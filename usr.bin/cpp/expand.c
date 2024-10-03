#include "globs.h"
#include "pipeline.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void
expand (int c)
{
	static size_t bufsz = 1;
	static size_t bufcp = 0;
	// possible macro char:
	if (isalnum(c) || c == '_')
	{
    	// grow buffer
		bufsz++;

		if (bufsz >= bufcp)
		{
			bufcp      = (3*bufsz)/2;
			expand_buf = (char *)realloc(expand_buf, bufcp);
			if (!expand_buf)
			{
				int errnum = errno;
				fprintf(stderr, "%s: Failed to allocate memory.\n", self);
				fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
				exit(1);
			}
		}
		// add character
		expand_buf[bufsz-1] = '\0';
		expand_buf[bufsz-2] = c; // add character

		return; // await next character
	}

	if (bufsz <= 1) // if no matched characters
	{
		goto print;
	}

	// check for macro
	if (!strcmp("__FILE__", expand_buf)) // __FILE__ special macro
	{
		fputc('"', fout);
		fwrite(filename, 1, strlen(filename), fout); // printf file name
		fputc('"', fout); // with quotes around

		goto reset_buffer;
	}
	else if (!strcmp("__LINE__", expand_buf)) // __LINE__ special macro
	{
		fprintf(fout, "%zu", lineno);
	}
// else if macro:
//     if macro has parameters:
//         expand parameters
//     expand concatenation
//     reset buffer
//     pass expansion through `expand'
	else
	{
    	// print buffer
		fwrite(expand_buf, 1, bufsz-1, fout);
	}

reset_buffer:
	bufsz = 1;
	expand_buf[0] = '\0';
print:
	// print c
	fputc(c, fout);
}
