#include "main.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

static long outputcp = 0;

long  outputsz  = 0;
void *outputBuf = NULL;

void
emit (void *buf, long amt)
{
	long oldSize = outputsz;
	outputsz += amt;
	if (outputsz > outputcp)
	{
		outputcp = 3*outputsz/2;
		void *newbuf = realloc(outputBuf, outputcp);
		if (!newbuf)
		{
			outputcp = outputsz-amt;
			errors++;
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			return;
		}
		outputBuf = newbuf;
	}

	memcpy(&outputBuf[oldSize], buf, amt);
	return ;
}
