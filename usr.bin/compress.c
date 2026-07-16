#include <libintl.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <zio.h>

const char *self;
int errors = 0;

#define OPTS_STDIN    1
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

void
compress (const char *path)
{
	errors = 1;
	fprintf(stderr, gettext("%s: Not implemented\n"), self);
}

void
decompress (const char *path)
{
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
			opts |= OPTS_STDIN;
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
		_setformat(ZIO_FORMAT_DEFAULT_COMPRESS);
	}

	if (errors) return 1;

	// parse operands
	if (opts & OPTS_DECOMP) // compress -d
	{
		for (int i = optind; i<argc; i++) // compress -d files...
		{
			decompress(argv[i]);
		}
		if (argc == optind) // compress -d
		{
			decompress("-");
		}
	}
	else
	{
		if (opts & OPTS_STDIN) // compress -c
		{
			if (argc == optind) // compress -c
			{
				compress("-");
			}
			else if (argc == (optind+1)) // compress -c file
			{
				compress(argv[optind]);
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
				compress(argv[i]);
			}
			if (argc == optind) // compress
			{
				compress("-");
			}
		}
	}

	if (opts & OPTS_BIGGER) return 2;
	if (errors) return 1;
	return 0;
}
