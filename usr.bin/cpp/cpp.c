#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"

const char *self = "/usr/bin/cpp";

// I/O
const char *filename; // default to standard input
FILE       *fin;
FILE       *fout;

// line number
size_t lineno;

// expand.c saved character buffer
char *expand_buf = (char *)NULL;
// directives.c saved character buffer
char *directive_buf = (char *)NULL;

void
buf_free (void)
{
	if (expand_buf)
	{
		free(expand_buf);
	}
	if (directive_buf)
	{
		free(directive_buf);
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

	atexit(buf_free);

	// line control
	fprintf(fout, "# 1 \"<command-line>\"\n");

	// parse command line options
	options(argc, argv);

	// reset line control
	lineno   = 0;
	filename = "<stdin>";
	fprintf(fout, "# 1 \"%s\"\n", filename);
	int c;
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
	lineSplicing(EOF);
}
