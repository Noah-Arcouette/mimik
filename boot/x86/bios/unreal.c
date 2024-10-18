#include "globs.h"
#include "colors.h"
#include "lang.h"
#include "unreal.h"

#define __STR(X) #X
#define STR(X) __STR(X)

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

	// open kernel file
	int kernel = fsopen(STR(KERNEL));
	if (kernel < 0) // failed to open
	{
		puts(NO_KERNEL_FILE, FG_RED);
		puts(STR(KERNEL), FG_WHITE);
		puts(NO_KERNEL_FILE2, FG_RED);
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
