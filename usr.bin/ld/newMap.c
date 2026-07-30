#include "main.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <mio.h>

struct MiO_Map *outputMap  = NULL;
long            outputMaps = 0;

void
newMap (const struct MiO_Map *map)
{
	outputMaps++;
	void *buf = realloc(outputMap, sizeof(struct MiO_Map)*outputMaps);
	if (!buf)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		outputMaps--;
		errors++;
		return;
	}
	outputMap = buf;

	memcpy(&outputMap[outputMaps-1], map, sizeof(struct MiO_Map));
}
