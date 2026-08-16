#include "functions.h"
#include <stddef.h>

struct mbr_part *
find_mbr_partition (void)
{
	struct mbr_part *p = MBR_PART1;

	for (int i = 0; i<4; i++)
	{
		if (p->flags & MBR_PART_FLAG_BOOTABLE)
		{
			return p;
		}

		p += sizeof(struct mbr_part);
	}
	return NULL;
}
