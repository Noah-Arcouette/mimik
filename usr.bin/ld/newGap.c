#include "parse.h"
#include "main.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>

struct MiO_Gap *outputGap   = NULL;
size_t          outputGapsz = 0;
size_t          outputGapcp = 0;

void
newGap (uint64_t offset, int type, const char *name)
{
	outputGapsz++;
	if (outputGapsz > outputGapcp)
	{
		outputGapcp = 3*outputGapsz/2;
		void *buf = realloc(outputGap, sizeof(struct MiO_Gap)*outputGapcp);
		if (!buf)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			outputGapsz--;
			outputGapcp = outputGapsz;
			return;
		}
		outputGap = buf;
	}

	struct MiO_Gap *g = &outputGap[outputGapsz-1];
	g->offset = htole64(offset);
	g->type   = htole16(type);
	memset(g->symbol, 0, sizeof(g->symbol));
	strncpy((char *)g->symbol, name, sizeof(g->symbol));
}
