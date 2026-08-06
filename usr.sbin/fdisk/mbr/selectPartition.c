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
	long last = 1; // LBA 1 (end of MBR)
	for (int j = 0; j<4; j++)
	{
		const struct mbr_part *q = &mbr.part[j];
		if (q->type == MBR_PART_TYPE_FREE) continue;

		int end = le32toh(q->firstLBA)+le32toh(q->sectors);
		if (end > last) last = end;
	}
	last *= bytesPerSector;
	// align
	if (alignment) last += alignment-(last%alignment); // no div by zero
	long size = diskSize-last;
	if (size < 0) size = 0; // no negatives
	if (last > (long)diskSize)
	{
		fprintf(stderr, gettext("%s: No room left on disk for MBR #%d\n"),
			self, i);
		errors++;
		partitionIndex = -1;
		return;
	}

	p->type  = MBR_PART_TYPE_FS;
	p->flags = 0;
	p->firstLBA = htole32(last/bytesPerSector);
	p->sectors  = htole32(size/bytesPerSector);
	mbr_updateCHS();
}
