#include "../emit.h"
#include "../main.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <errno.h>

static struct MiO_Gap *gap  = NULL;
static size_t          gaps = 0;

void
emitGapData (void)
{
	emitSection((char *)MIO_SPECIAL_MIO_GAPS);
	emit(gap, gaps*sizeof(struct MiO_Gap));

	free(gap);
	gap  = NULL;
	gaps = 0;
}

void
emitGap (const char *symbol, int type)
{
	// make sure we're in a section
	if (currentSection < 0)
	{
		prettyprint("Must be in a section to emit a gap\n");
		errors++;
		return;
	}

	struct MiO *csect = (void *)&emitbuf[currentSection];
	// make sure we're not in a data section
	if (csect->flags & MIO_FLAG_VIRTUAL)
	{
		prettyprint("Gaps may not be in virtual sections\n");
		errors++;
		return;
	}

	// make sure the symbol fits
	if (strlen(symbol) > 256)
	{
		prettyprint("Symbol name too long\n");
		errors++;
		return;
	}

	// create the new gap
	gaps++;
	void *buf = realloc(gap, sizeof(struct MiO_Gap)*gaps);
	if (!buf)
	{
		gaps--;
		int error = errno;
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(error));
		errors++;
		return;
	}
	gap = buf;
	struct MiO_Gap *g = &gap[gaps-1];

	// fill in data
	memset(g, 0, sizeof(*g));
	strncpy((void *)g->symbol, symbol, sizeof(g->symbol));
	g->offset = htole64(emitsz);
	g->type   = htole16(type);

	// emit zeros data
	int size = 0;
	switch (type)
	{
	case MIO_GAP_TYPE_LIT_BYTE:
	case MIO_GAP_TYPE_DISP_BYTE:
		size = 1;
		break;
	case MIO_GAP_TYPE_LIT_LE16:
	case MIO_GAP_TYPE_LIT_BE16:
	case MIO_GAP_TYPE_DISP_BE16:
	case MIO_GAP_TYPE_DISP_LE16:
		size = 2;
		break;
	case MIO_GAP_TYPE_LIT_LE32:
	case MIO_GAP_TYPE_LIT_BE32:
	case MIO_GAP_TYPE_DISP_LE32:
	case MIO_GAP_TYPE_DISP_BE32:
		size = 4;
		break;
	case MIO_GAP_TYPE_LIT_LE64:
	case MIO_GAP_TYPE_DISP_BE64:
	case MIO_GAP_TYPE_DISP_LE64:
	case MIO_GAP_TYPE_LIT_BE64:
		size = 8;
		break;
	case MIO_GAP_TYPE_LIT_LE128:
	case MIO_GAP_TYPE_DISP_BE128:
	case MIO_GAP_TYPE_DISP_LE128:
	case MIO_GAP_TYPE_LIT_BE128:
		size = 16;
		break;
	}

	char zeros[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	emit(zeros, size);
}
