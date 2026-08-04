#include "main.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void
readIn (const char *path)
{
	FILE *infp;
	if (!strcmp(path, "-"))
	{
		infp = stdin;
	}
	else
	{
		infp = fopen(path, "r");
		if (!infp)
		{
			fprintf(stderr,
				gettext("%s: Failed to open file `%s' for reading, %s\n"),
				self, path, strerror(errno));
			errors++;
			return;
		}
	}

	// the buffer capacity
	long bufcp = bufsz;

	// read in data
	char inbuf[BUFSIZ];
	while (1)
	{
		long amt = fread(inbuf, 1, BUFSIZ, infp);

		// grow the output buffer
		bufsz += amt;
		if (bufsz > bufcp)
		{
			bufcp = 3*bufsz/2;
			void *newbuf = realloc(buf, bufcp);
			if (!newbuf)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				bufsz -= amt;
				errors++;
				break;
			}
			buf = newbuf;
		}

		// copy the data
		memcpy(&buf[bufsz-amt], inbuf, amt);

		if (amt != BUFSIZ)
		{
			if (feof(infp)) break;

			fprintf(stderr, gettext("%s: Failed to read from file `%s', %s\n"),
				self, path, strerror(errno));
			bufsz -= amt;
			errors++;
			break;
		}
	}

	// shrink the buffer
	void *newbuf = realloc(buf, bufsz);
	if (newbuf) buf = newbuf; // we don't really care if it fails

	// close it
	fclose(infp);
}
