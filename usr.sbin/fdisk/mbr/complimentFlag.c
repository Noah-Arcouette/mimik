#include "../main.h"
#include <libintl.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void
mbr_complimentFlag (const char *flag)
{
	if (partitionIndex > 3)
	{
		fprintf(stderr, gettext(
			"%s: Refusing to compliment flag of partition higher than 3\n"),
			self);
		errors++;
		return;
	}

	struct mbr_part *p = &mbr.part[partitionIndex];

	if (!strcasecmp(flag, "boot"))
	{
		p->flags ^= MBR_PART_FLAG_BOOTABLE;
	}
	else
	{
		fprintf(stderr, gettext("%s: Unknown flag %s\n"), self, flag);
		errors++;
	}
}
