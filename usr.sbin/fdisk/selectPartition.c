#include "main.h"
#include <libintl.h>
#include <stdio.h>

int partitionIndex = -1;

void
selectPartition (int i)
{
	partitionIndex = -1;
	switch (partMode)
	{
	case MODE_NONE:
		fprintf(stderr,
			gettext("%s: No partition map selected for partition\n"), self);
		errors++;
		break;
	case MODE_MBR:
	#ifdef MBR
		mbr_selectPartition(i);
	#endif
		break;
	}
}
