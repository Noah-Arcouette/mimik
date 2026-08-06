#include "main.h"
#include <libintl.h>
#include <stdio.h>

void
complimentFlag (const char *flag)
{
	if (partitionIndex < 0)
	{
		fprintf(stderr, gettext(
			"%s: Refusing to compliment flag without selected partition\n"),
			self);
		errors++;
		return;
	}

	switch (partMode)
	{
	case MODE_NONE:
		fprintf(stderr, gettext(
			"%s: Refusing to compliment flag outside of partition map\n"),
			self);
		errors++;
		break;
	case MODE_MBR:
	#ifdef MBR
		mbr_complimentFlag(flag);
	#endif
		break;
	}
}
