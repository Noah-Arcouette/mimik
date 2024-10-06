#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
main (int argc, const char **argv)
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
	while (1)
	{
		c = getopt(argc, argv, ":U:");
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
			const char *undef = "#undef ";
			while (*undef) // print undefine
			{
				lineSplicing(*undef);
				undef++;
			}
			const char *string = optarg;
			while (*string) // give the given value
			{
				lineSplicing(*string);
				string++;
			}
			lineSplicing('\n'); // newline
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
