#include "../unreal.h"
#include "../colors.h"
#include "../lang.h"

struct MBR_Part
{
	unsigned char status; // the status flags of the partition

	// first block
	unsigned char firstHead;
	unsigned char firstSector;
	unsigned char firstCylinder;

	// partition type
	unsigned char type;

	// last block
	unsigned char lastHead;
	unsigned char lastSector;
	unsigned char lastCylinder;

	// LBA
	unsigned int lba;     // first LBA
	unsigned int sectors; // amount of sectors in partition
} __attribute__((packed));

struct MBR
{
	unsigned char bootstrap1[446];
	struct MBR_Part partitions[4];
	unsigned char signature[2];
} __attribute__((packed));

int
getPartitionInfo(void)
{
	struct MBR mbr;

	// Read first sector into MBR structure
	if (diskRead(0, 1, (void*)&mbr))
	{
		return 1;
	}

	// check mbr signature
	if (mbr.signature[0] != 0x55 || mbr.signature[1] != 0xaa)
	{
		puts(MBR_SIGNATURE, FG_RED);
		return 1;
	}

	// find boot partition
	for (int i = 0; i<4; i++)
	{
		struct MBR_Part part = mbr.partitions[i];
		// check for boot flag
		if (part.status & 0x80)
		{
			pinfo.start = part.lba;
			return 0;
		}
	}

	puts(PART_NO_PART, FG_RED);
	return 1;
}
