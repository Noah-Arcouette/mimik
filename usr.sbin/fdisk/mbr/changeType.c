#include "../main.h"
#include <libintl.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void
mbr_changeType (const char *type)
{
	if (partitionIndex > 3)
	{
		fprintf(stderr,
			gettext("%s: Refusing to set type of partition higher than 3\n"),
			self);
		errors++;
		return;
	}

	struct mbr_part *p = &mbr.part[partitionIndex];

	if (!strcasecmp(type, "vbr"))
	{
		p->type = MBR_PART_TYPE_VBR;
	}
	else if (!strcasecmp(type, "root"))
	{
		p->type = MBR_PART_TYPE_ROOT;
	}
	else if (!strcasecmp(type, "fs"))
	{
		p->type = MBR_PART_TYPE_FS;
	}
	else if (!strcasecmp(type, "none"))
	{
		memset(p, 0, sizeof(struct mbr_part)); // clear it
	}
	else
	{
		p->type = strtol(type, NULL, 16) & 0xff;
	}
}
