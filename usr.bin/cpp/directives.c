#include "pipeline.h"
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "globs.h"

void
directives (int c)
{
	static int    state = 0;
	static size_t bufsz = 1; // buffer size
	static size_t bufcp = 0; // buffer capacity

	static size_t name; // directive name index
	static size_t namesz; // size of the directive name

	// add to buffer
	bufsz++;
	if (bufsz > bufcp)
	{
		bufcp         = (3*bufsz)/2;
		directive_buf = (char *)realloc(directive_buf, bufcp);
		if (!directive_buf) // failed to allocate
		{
			int errnum = errno;
			fprintf(stderr, "%s: Failed to allocate memory.\n", self);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
			exit(1);
		}
	}
	directive_buf[bufsz-2] = c; // add character
	directive_buf[bufsz-1] = '\0'; // terminate string

check: // for rerunning check on state change
	switch (state)
	{
	// find `#'
	case 0:
		if (isspace(c) && c != '\n')
		{
			return; // ignore it
		}
		if (c == '#')
		{
			state++; // next state
			return;
		}
		state = -1; // ignore the rest of the line
		goto check;
	// eat spaces
	case 1:
		if (isspace(c) && c != '\n')
		{
			return; // ignore spaces
		}
		name = bufsz-2;
		state++; // next state
		goto check;
	// capture directive name
	case 2:
		if (isalpha(c))
		{
			return; // ignore characters
		}
		namesz = (bufsz-2)-name; // save size of the directive name
		state++; // next state after directive name is captured
		goto check;
	// capture directive options
	case 3:
		if (c == '\n')
		{
			// check and parse directive found, or just emit verbatim
			printf("`%s' `%s' %zu\n", directive_buf, directive_buf+name, namesz);

			// emit and restart
			state = -1; // finish on newline
			goto check;
		}
		return; // ignore the rest
	// flush buffer
	case -1:
		for (size_t i = 0; i<(bufsz-1); i++)
		{
			expand(directive_buf[i]);
		}
		bufsz = 1; // reset buffer
		state = 0; // reset state
		break;
	}
}
