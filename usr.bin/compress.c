#include <sys/stat.h>
#include <libintl.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <zio.h>

const char *self;
int errors = 0;

#define OPTS_STDOUT   1
#define OPTS_DECOMP   2
#define OPTS_FORCE    4
#define OPTS_KEEP     8
#define OPTS_VERBOSE 16
// file was made bigger
// this isn't an options but I'm using the bit field anyways
#define OPTS_BIGGER  32
int opts = 0;
int level = -1;
int format = -1;
int threads = 1;

static void
_setformat (int f)
{
	if (format >= 0)
	{
		fprintf(stderr, gettext("%s: Format set twice\n"), self);
		errors++;
	}

	format = f;

	if (level < 0)
	{
		if (format == ZIO_FORMAT_LZW) level = 16;
		else level = 6;
	}
}

static void
_compress (const char *path)
{
	zFILE *out     = NULL;
	char  *outname = NULL;
	FILE  *in      = NULL;

	int _stdin = 0;
	if (!strcmp(path, "-")) _stdin = 1;

	if (opts & OPTS_STDOUT || _stdin) // compress -c
	{
		if (isatty(STDOUT_FILENO)) // make sure its not a tty
		{
			fprintf(stderr, gettext("%s: Refusing to write to a tty\n"), self);
			errors++;
			return;
		}

		outname = "<stdout>";
		out = zdopen(STDOUT_FILENO, "w", format);
		if (!out)
		{
			fprintf(stderr, gettext("%s: Failed to zdopen file, `%s', %s\n"),
				self, outname, strerror(errno));
			errors++;
			goto comp_leave;
		}
	}
	else
	{
		// make file name
		const char *suffix = z_suffix_from_format(format);
		outname = malloc(
			strlen(path)
			+1 // period
			+strlen(suffix)
			+1 // terminator
		);

		if (!outname)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			return;
		}
		strcpy(outname, path);
		strcat(outname, ".");
		strcat(outname, suffix);

		// check if it already exists
		if (!(opts & OPTS_FORCE))
		{
			if (!access(outname, F_OK))
			{
				fprintf(stderr,
					gettext("%s: File `%s' already exists, overwrite? "),
					self, outname);

				/// @todo if (!yesno())
				{
					errors++;
					goto comp_leave;
				}
			}
		}

		// zopen file
		out = zopen(outname, "w", format);
		if (!out)
		{
			fprintf(stderr, gettext("%s: Failed to zopen file, `%s', %s\n"),
				self, outname, strerror(errno));
			errors++;
			goto comp_leave;
		}

		if (!_stdin)
		{
			// stat input
			struct stat statbuf;
			if (stat(path, &statbuf))
			{
				fprintf(stderr, gettext("%s: Failed to stat file, `%s', %s\n"),
					self, path, strerror(errno));
				errors++;
				goto comp_leave;
			}

			// copy meta data, we don't care if it fails
			zchown(out, statbuf.st_uid, statbuf.st_gid);
			zchmod(out, statbuf.st_mode);
			struct timespec t[2];
			t[0].tv_nsec = statbuf.st_atim.tv_nsec;
			t[0].tv_sec  = statbuf.st_atim.tv_sec;
			t[1].tv_nsec = statbuf.st_mtim.tv_nsec;
			t[1].tv_sec  = statbuf.st_mtim.tv_sec;
			zutimens(out, t);
		}
	}

	// check for stdin
	if (_stdin)
	{
		if (isatty(STDIN_FILENO)) // make sure its not a tty
		{
			fprintf(stderr, gettext("%s: Refusing to read from a tty\n"), self);
			errors++;
			goto comp_leave;
		}

		in = stdin;
		path = "<stdin>";
	}
	else
	{
		// open path
		in = fopen(path, "r");
		if (!in)
		{
			fprintf(stderr, gettext("%s: Failed to open file, `%s', %s\n"),
				self, path, strerror(errno));
			errors++;
			goto comp_leave;
		}
	}

	// set compression options
	z_set_cores(out, threads);
	z_set_original_name(out, path);
	if (format == ZIO_FORMAT_LZW)
	{
		if (z_set_codeword_bits(out, level))
		{
			fprintf(stderr,
				gettext("%s: Failed to set codeword bits for file `%s', %s\n"),
				self, outname, strerror(errno));
			errors++;
			goto comp_leave;
		}
	}
	else
	{
		if (z_set_compression_level(out, level))
		{
			fprintf(stderr,	gettext(
				"%s: Failed to set compression level for file `%s', %s\n"),
				self, outname, strerror(errno));
			errors++;
			goto comp_leave;
		}
	}

	// copy data
	char buf[BUFSIZ];
	size_t amt;
	size_t inpsiz = 0;
	do
	{
		amt = fread(buf, 1, BUFSIZ, in);
		if (amt < BUFSIZ)
		{
			int error = errno;
			if (ferror(in))
			{
				fprintf(stderr, gettext("%s: Failed to read from, `%s', %s\n"),
					self, path, strerror(error));
				errors++;
				goto comp_leave;
			}
		}
		inpsiz += amt;

		if (zwrite(buf, 1, amt, out) != amt)
		{
			fprintf(stderr, gettext("%s: Failed to write to, `%s', %s\n"),
				self, outname, strerror(errno));
			errors++;
			goto comp_leave;
		}
	} while (amt == BUFSIZ);

	// close output file
	zclose(out);
	out = NULL;
	fclose(in);
	in = NULL;

	// check size
	if (!(opts & OPTS_STDOUT))
	{
		struct stat statbuf;
		if (!stat(outname, &statbuf))
		{
			if (opts & OPTS_VERBOSE)
			{
				fprintf(stderr, gettext("%s: `%s' -> `%s' (%02f%%)\n"),
					self, path, outname,
					((float)statbuf.st_size*100.0f)/(float)inpsiz);
			}
			if (!(opts & OPTS_FORCE))
			{
				if ((size_t)statbuf.st_size >= inpsiz)
				{
					opts |= OPTS_BIGGER;
					unlink(outname);
					fprintf(stderr,
						gettext("%s: Failed to compress file `%s'\n"),
						self, path);
					goto comp_leave;
				}
			}
		}
		else
		{
			fprintf(stderr, gettext("%s: Failed to stat file, `%s', %s\n"),
				self, outname, strerror(errno));
		}
	}

	// delete file
	if (!(opts & OPTS_KEEP) && strcmp(path, "<stdin>"))
	{
		unlink(path);
	}

	// clean up
comp_leave:
	if (!(opts & OPTS_STDOUT))
	{
		free(outname);
	}
	if (out) zclose(out);
	if (in) fclose(in);
}

static void
_decompress (const char *path)
{
	/// @todo make file name
	/// @todo zopen path
	/// @todo copy metadata
	/// @todo open file
	/// @todo copy data
	/// @todo clean up

	errors = 1;
	fprintf(stderr, gettext("%s: Not implemented\n"), self);
}

int
main (int argc, char *argv[])
{
	textdomain("compress");
	setlocale(LC_ALL, "");
	self = argv[0];

	// parse options
	int c;
	do
	{
		c = getopt(argc, argv, "b:cdfgkm:p:v");
		int f;

		switch (c)
		{
		case 'b':
			level = strtol(optarg, NULL, 0);
			break;
		case 'c':
			opts |= OPTS_STDOUT;
			break;
		case 'd':
			opts |= OPTS_DECOMP;
			break;
		case 'f':
			opts |= OPTS_FORCE;
			break;
		case 'g':
			_setformat(ZIO_FORMAT_GZIP);
			break;
		case 'k':
			opts |= OPTS_KEEP;
			break;
		case 'm':
			f = z_format_from_name(optarg);
			if (f == -1)
			{
				fprintf(stderr, gettext("%s: Unknown format `%s'\n"), self,
					optarg);
				errors++;
			}
			_setformat(f);
			break;
		case 'p':
			threads = strtol(optarg, NULL, 0);
			break;
		case 'v':
			opts |= OPTS_VERBOSE;
			break;
		case '?':
		case ':':
			errors++;
			break;
		case -1:
			break;
		default:
			fprintf(stderr, gettext("%s: Uncaught option `-%c'\n"), self, c);
			errors++;
			break;
		}
	} while (c != -1);

	// set defaults
	if (format == -1)
	{
	#if defined(DEFAULT_LZW)
		_setformat(ZIO_FORMAT_LZW);
	#elif defined(DEFAULT_DEFLATE)
		_setformat(ZIO_FORMAT_DEFLATE);
	#elif defined(DEFAULT_GZIP)
		_setformat(ZIO_FORMAT_GZIP);
	#else
	# 	error "No default format found"
	#endif
	}

	if (errors) return 1;

	// check format, format stuff
	if (!z_format_is_filed(format))
	{
		fprintf(stderr,
			gettext("%s: Format `%s' is not a filed-based format\n"),
			self,
			z_name_from_format(format));
		return 1;
	}

	if (!z_format_is_compressed(format))
	{
		fprintf(stderr, gettext("%s: Format `%s' is not compressing\n"), self,
			z_name_from_format(format));
		return 1;
	}

	// parse operands
	if (opts & OPTS_DECOMP) // compress -d
	{
		for (int i = optind; i<argc; i++) // compress -d files...
		{
			_decompress(argv[i]);
		}
		if (argc == optind) // compress -d
		{
			_decompress("-");
		}
	}
	else
	{
		if (opts & OPTS_STDOUT) // compress -c
		{
			if (argc == optind) // compress -c
			{
				_compress("-");
			}
			else if (argc == (optind+1)) // compress -c file
			{
				_compress(argv[optind]);
			}
			else // compress -c files...
			{
				fprintf(stderr,
					gettext("%s: compress -c may only have one input file\n"),
					self);
				errors++;
			}
		}
		else
		{
			for (int i = optind; i<argc; i++) // compress files...
			{
				_compress(argv[i]);
			}
			if (argc == optind) // compress
			{
				_compress("-");
			}
		}
	}

	if (opts & OPTS_BIGGER) return 2;
	if (errors) return 1;
	return 0;
}
