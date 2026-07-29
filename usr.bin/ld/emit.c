#include "parse.h"
#include "main.h"
#include "lex.h"
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

	if (currentSection >= 0 &&
		((long)(currentSection+sizeof(struct MiO)) <= outputsz))
	{
		struct MiO *s = &outputBuf[currentSection];
		uint64_t size = le64toh(s->size);
		size += amt;
		s->size = htole64(size);

		if (s->flags & MIO_FLAG_VIRTUAL)
		{
			prettyprint(gettext("Attempted to emit data in virtual section\n"));
			errors++;
		}
	}

	memcpy(&outputBuf[oldSize], buf, amt);
	return ;
}
