#include <libintl.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/**
 * Read in the head of a file
 * @note This does not print file prologue messages
 * @returns True if an error occurred
 * @param filename The file to open, or stdin if "-"
 * @param lines The amount of lines to print if non-zero
 * @param bytes The amount of bytes to print if non-zero
 */
int
headFile (const char *filename, int lines, int bytes)
{
	FILE *fp;

	// standard input
	if (!strcmp(filename, "-"))
	{
		fp = stdin;
	}
	// open file
	else
	{
		fp = fopen(filename, "r");
		if (!fp)
		{
			int error = errno;
			fprintf(stderr, gettext("%s: %s\n"), filename, strerror(error));
			return 1;
		}
	}

	// print the file lines
	if (lines)
	{
		while (lines > 0)
		{
			int c = getc(fp);
			if (c == EOF)
			{
				if (ferror(fp))
				{
					perror("getc");
					fclose(fp);
					return 1;
				}
				break;
			}
			else if (c == '\n') lines--;

			putc(c, stdout);
		}
	}
	// print the file bytes
	else
	{
		while (bytes > 0)
		{
			int c = getc(fp);
			if (c == EOF)
			{
				if (ferror(fp))
				{
					perror("getc");
					fclose(fp);
					return 1;
				}
				break;
			}
			bytes--;

			putc(c, stdout);
		}
	}

	fclose(fp);
	return 0;
}

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("head");

	int lines = 0;
	int bytes = 0;
	int quiet = 0;

	int c;
	do
	{
		c = getopt(argc, argv, "qn:c:");

		switch (c)
		{
		case 'q':
			quiet = 1;
			break;
		case 'n':
			if (bytes || lines)
			{
				fprintf(stderr,
					gettext("%s: Head count set more than once\n"),
					argv[0]);
				return 1;
			}
			lines = strtol(optarg, NULL, 10);
			if (lines <= 0)
			{
				fprintf(stderr,
					gettext("%s: Line count must be greater than zero\n"),
					argv[0]);
				return 1;
			}
			break;
		case 'c':
			if (bytes || lines)
			{
				fprintf(stderr,
					gettext("%s: Head count set more than once\n"),
					argv[0]);
				return 1;
			}
			bytes = strtol(optarg, NULL, 10);
			if (bytes <= 0)
			{
				fprintf(stderr,
					gettext("%s: Byte count must be greater than zero\n"),
					argv[0]);
				return 1;
			}
			break;
		case '?':
		case ':':
			return 1;
		}
	} while (c != -1);

	// default
	if (!bytes && !lines) lines = 10;

	// read in the files
	if (argc == optind) // no operands
	{
		return headFile("-", lines, bytes);
	}
	// else, one file
	if (argc == optind+1)
	{
		return headFile(argv[optind], lines, bytes);
	}
	// else, print multiple with file name prologue
	for (int i = optind; i<argc; i++)
	{
		if (i == optind && !quiet)
		{
			printf("==> %s <==\n", argv[i]);
		}
		else if (!quiet)
		{
			printf("\n==> %s <==\n", argv[i]);
		}

		if (headFile(argv[i], lines, bytes)) return 1;
	}

	return 0;
}
