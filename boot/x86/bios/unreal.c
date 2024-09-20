#include "globs.h"
#include "colors.h"
#include "lang.h"
#include "unreal.h"

struct diskInfo  dinfo;
struct partInfo  pinfo;
struct memoryMap map[MAX_MAP];
unsigned int     maps = 0;

void
_unreal (void)
{
	// get memory map and info
	if (getMemoryMap())
	{
		goto leave;
	}

	// get disk info
	if (getDiskInfo(bootDisk))
	{
		goto leave;
	}

	// get partition info
	if (getPartitionInfo())
	{
		goto leave;
	}

	// load boot file
	if (fsInit())
	{
		goto leave;
	}

	// FS Read, size, buf, amount
	// Object Load, memmap

	// setup page directory
	// kmap

	// setup GDT, IDT, and LDT

	// enter kernel

leave:
	halt();
}
