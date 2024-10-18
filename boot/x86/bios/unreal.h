#ifndef __UNREAL_H__
#define __UNREAL_H__
#include <stdnoreturn.h>

// puts.c
extern void puts (const char *, char);

// putc.c
extern void putc (char, unsigned char);

// halt.c
extern noreturn void halt (void);

// putnum.c
extern void putnum (unsigned int, unsigned int, unsigned char);

// getDiskInfo.c
struct diskInfo
{
	unsigned char  disk;
	unsigned char  heads;
	unsigned short cylinders;
	unsigned short sectors;
};
extern int getDiskInfo (unsigned char);

// diskError.c
extern void diskError (unsigned char);

// part/<type>
struct partInfo
{
	// offset into disk for the partition
	unsigned int start;
};

extern int getPartitionInfo(void);

// diskRead.c
extern int diskRead (unsigned int, unsigned char, void *);

// mem.c
#define MEMORY_MAP_USABLE       1
#define MEMORY_MAP_RESERVED     2
#define MEMORY_MAP_ACPI_RECLAIM 3
#define MEMORY_MAP_ACPI_NVS     4
#define MEMORY_MAP_BAD          5
struct memoryMap
{
	unsigned int baseL;
	unsigned int baseH;
	unsigned int lenL;
	unsigned int lenH;
	unsigned int type;
	unsigned int ACPI;
} __attribute__((packed));
extern int getMemoryMap (void);

#ifndef MAX_MAP
#	define MAX_MAP 64
#endif

// unreal.c
extern struct partInfo  pinfo;
extern struct diskInfo  dinfo;
extern struct memoryMap map[MAX_MAP];
extern unsigned int     maps;

// fs/<type>
extern int fsopen (const char *);
extern int fsread (unsigned int, unsigned int, unsigned int, void *);

// strcmp.c
int strncmp (const char *restrict, const char *restrict, unsigned int);

#endif
