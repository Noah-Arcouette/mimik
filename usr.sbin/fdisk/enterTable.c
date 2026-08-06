#include "main.h"
#include <libintl.h>
#include <strings.h>
#include <stdio.h>

enum partMode partMode = MODE_NONE;

void
enterTable (const char *table, int load)
{
	if (!strcasecmp(table, "mbr"))
	{
	#ifdef MBR
		partMode = MODE_MBR;
		mbr_enterTable(load, 0);
	#else
		partMode = MODE_NONE;
		fprintf(stderr, gettext("%s: MBR partitioning not installed\n"), self);
		errors++;
	#endif
	}
	else
	{
		partMode = MODE_NONE;
		fprintf(stderr, gettext("%s: Unknown mode `%s'\n"), self, table);
		errors++;
	}
}
