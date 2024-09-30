#include <stdio.h>
#include <stdlib.h>
#include "pipeline.h"

const char *self = "/usr/bin/cpp";

// I/O
const char *filename = "<stdin>"; // default to standard input
FILE       *fin;
FILE       *fout;

// line number
size_t lineno = 0;

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

    // read each character
    int c;
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
