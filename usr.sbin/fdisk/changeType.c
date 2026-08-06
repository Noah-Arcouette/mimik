#include "main.h"
#include <libintl.h>
#include <stdio.h>

void
changeType (const char *type)
{
	if (partitionIndex < 0)
	{
		fprintf(stderr,
			gettext("%s: Refusing to set type without selected partition\n"),
			self);
		errors++;
		return;
	}

	switch (partMode)
	{
	case MODE_NONE:
		fprintf(stderr,
			gettext("%s: Refusing to set type outside of partition map\n"),
			self);
		errors++;
		break;
	case MODE_MBR:
	#ifdef MBR
		mbr_changeType(type);
	#endif
		break;
	}
}
