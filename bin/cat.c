#include <libintl.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

int
cat (const char *path, int buffering)
{
	FILE *fp;
	// open the file
	if (!strcmp(path, "-")) // standard input
	{
		fp = stdin;
	}
	else
	{
		fp = fopen(path, "r");
		if (!fp)
		{
			int error = errno;
			fprintf(stderr, gettext("%s: %s\n"), path, strerror(error));
			return 1;
		}
	}

	// buffering
	if (buffering)
	{
		char buf[BUFSIZ];

		while (1)
		{
			size_t sz = fread(buf, 1, BUFSIZ, fp);
			int error = errno;
			if (ferror(fp))
			{
				fprintf(stderr, gettext("%s: %s\n"), path, strerror(error));
				if (fp != stdin) fclose(fp);
				return 1;
			}

			fwrite(buf, 1, sz, stdout);
			error = errno;
			if (ferror(stdout))
			{
				fprintf(stderr, gettext("%s: %s\n"), path, strerror(error));
				if (fp != stdin) fclose(fp);
				return 1;
			}

			if (sz < BUFSIZ)
			{
				if (fp != stdin) fclose(fp);
				return 0;
			}
		}
		assert(0);
	}
	// else, non-buffering
	if (setvbuf(fp, NULL, _IONBF, 0))
	{
		int error = errno;
		fprintf(stderr, gettext("%s: %s\n"), path, strerror(error));
		if (fp != stdin) fclose(fp);
		return 1;
	}

	while (1)
	{
		char c = fgetc(fp);
		int error = errno;
		if (ferror(fp))
		{
			fprintf(stderr, gettext("%s: %s\n"), path, strerror(error));
			if (fp != stdin) fclose(fp);
			return 1;
		}

		if (c == EOF)
		{
			if (fp != stdin) fclose(fp);
			return 0;
		}

		fputc(c, stdout);
		error = errno;
		if (ferror(stdout))
		{
			fprintf(stderr, gettext("%s: %s\n"), path, strerror(error));
			if (fp != stdin) fclose(fp);
			return 1;
		}
	}
	assert(0);
}

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("cat");

	int buffering = 1;

	// parse command line arguments
	int c;
	do
	{
		c = getopt(argc, argv, "u");

		switch (c)
		{
		// disable blocking on input and output
		case 'u':
			setvbuf(stdout, NULL, _IONBF, 0);
			setvbuf(stdin,  NULL, _IONBF, 0);
			buffering = 0;
			break;
		case '?':
		case ':':
			return 1;
		}
	} while (c != -1);

	// no files
	if (optind == argc)
	{
		return cat("-", buffering);
	}
	// else
	// parse the files
	for (int i = optind; i<argc; i++)
	{
		if (cat(argv[i], buffering))
		{
			return 1;
		}
	}

	return 0;
}
