#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pipeline.h"

const char *self = "/usr/bin/cpp";

// I/O
const char *filename; // default to standard input
FILE       *fin;
FILE       *fout;

// line number
size_t lineno;

// expand.c saved character buffer
char *expand_buf = (char *)NULL;

void
expand_buf_free (void)
{
	if (expand_buf)
	{
		free(expand_buf);
	}
}

int
main (int argc, char * const*argv)
{
	// defaults
	fin  = stdin;
	fout = stdout;

	// find program name
	if (argc > 0)
	{
		self = argv[0];
	}

	atexit(expand_buf_free);

	// line control
	fprintf(fout, "# 1 \"<command-line>\"\n");

	// parse command line options
	filename = "<command-line>";
	int c;
	opterr = 0; // no outputs
	lineno = 1;
	char *string;
	while (1)
	{
		c = getopt(argc, argv, ":U:D:");
		if (c < 0)
		{
			break; // leave on end of getopt
		}

		switch (c)
		{
		case '?':
			fprintf(stderr, "%s:%zu: Unknown option `%c'\n", filename, lineno, optopt);
			exit(1);
			break;
		case ':':
			fprintf(stderr, "%s:%zu: Option `%c' requires a parameter.\n", filename, lineno, optopt);
			exit(1);
			break;
		case 'U':
			string = "#undef ";
			while (*string) // print undefine
			{
				lineSplicing(*string);
				string++;
			}
			string = optarg;
			while (*string) // give the given value
			{
				lineSplicing(*string);
				string++;
			}
			lineSplicing('\n'); // newline
			break;
		case 'D':
			string = "#define ";
			while (*string) // print define
			{
				lineSplicing(*string);
				string++;
			}

			// convert first `=' to a space
			char *eq = strchr(optarg, '=');
			if (eq) // there may not be one
			{
				*eq = ' ';
			}

			string = optarg;
			while (*string) // give the given value
			{
				lineSplicing(*string);
				string++;
			}
			lineSplicing('\n');
			break;
		}
		lineno++;
	}

	// reset line control
	lineno   = 0;
	filename = "<stdin>";
	fprintf(fout, "# 1 \"%s\"\n", filename);
	// read each character
	while ((c = fgetc(fin)) != EOF)
	{
		if (c == '\n')
		{
			lineno++;
		}

		// send character down the pipeline, starting at line splicing
		lineSplicing(c);
	}
}
