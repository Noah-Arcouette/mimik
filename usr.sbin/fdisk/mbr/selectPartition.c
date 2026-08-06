#include "../main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>

void
mbr_selectPartition (int i)
{
	if (i < 0 || i > 3)
	{
		fprintf(stderr, gettext("%s: Partition #%d out of MBR range [0, 3]\n"),
			self, i);
		errors++;
		return;
	}

	partitionIndex = i;
	struct mbr_part *p = &mbr.part[i];

	// already exists
	if (p->type != MBR_PART_TYPE_FREE) return;
	// else, create it

	// find the last address
	int last = 1; // LBA 1 (end of MBR)
	for (int i = 0; i<4; i++)
	{
		if (p->type == MBR_PART_TYPE_FREE) continue;

		int end = le32toh(p->firstLBA)+le32toh(p->sectors);
		if (end > last) end = last;
	}
	last *= bytesPerSector;
	// align
	if (alignment) last += alignment-(last%alignment); // no div by zero
	int size = diskSize-last;
	if (size < 0) size = 0; // no negatives

	p->type  = MBR_PART_TYPE_FS;
	p->flags = 0;
	p->firstLBA = htole32(last/bytesPerSector);
	p->sectors  = htole32(size/bytesPerSector);
	mbr_updateCHS();
}
