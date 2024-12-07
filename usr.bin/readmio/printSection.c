#include <endian.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <mio.h>
#include "defs.h"

void
printSection (FILE *fp, struct MiO_Section s)
{
	printf("Name:  `%.*s'\n", (int)sizeof(s.name), s.name);
	printf("Offset: %lu\n", le64toh(*((uint64_t *)s.offset)));
	printf("Size:   %lu\n", le64toh(*((uint64_t *)s.size)));
	printf("Flags:  ");
	if (s.flags & MIO_SECTION_FLAG_PERMISSION_READ)
	{
		printf("Readable ");
	}
	if (s.flags & MIO_SECTION_FLAG_PERMISSION_WRITE)
	{
		printf("Writable ");
	}
	if (s.flags & MIO_SECTION_FLAG_PERMISSION_EXECUTE)
	{
		printf("Executable ");
	}
	if (s.flags & MIO_SECTION_FLAG_BSS)
	{
		printf("Non-Initialized-Data ");
	}
	if (s.flags & MIO_SECTION_FLAG_LAST)
	{
		printf("Last");
	}
	printf("\n");

	// is it a special section
	if (!strncmp((char *)s.name, MIO_LIB_NAME, sizeof(s.name)))
	{
		printLibraries(fp, s);
	}
	else if (!strncmp((char *)s.name, MIO_SYMLIST_NAME, sizeof(s.name)))
	{
		printSymbolList(fp, s);
	}
	else if (!strncmp((char *)s.name, MIO_GAP_NAME, sizeof(s.name)))
	{
		printGaps(fp, s);
	}
	else if (!strncmp((char *)s.name, MIO_MAP_NAME, sizeof(s.name)))
	{
		printMap(fp, s);
	}
}
