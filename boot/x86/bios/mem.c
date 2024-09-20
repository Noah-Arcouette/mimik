#include "unreal.h"
#include "colors.h"
#include "lang.h"

#define MAP_SIG 0x534d4150 // "SMAP" System Map

int
getMemoryMap (void)
{
	puts(MEMORY_MAP_HEADER, FG_CYAN);

	unsigned int cont = 0;
	int sig;
	int bytes;
	do
	{
		__asm (
			"int $0x15\n"
			: "=a"(sig),      // magic
			  "=c"(bytes),
			  "=b"(cont)      // continuation id
			: "a"(0xe820),    // e820 BIOS get memory map
			  "b"(cont),      // continuation id
			  "c"(sizeof(struct memoryMap)),
			  "d"(MAP_SIG),   // magic
			  "D"(&map[maps]) // output
		);

		if (sig != MAP_SIG)
		{
			puts(MEMORY_MAP_FAILED, FG_RED);
			return 1;
		}
		if (bytes > 20 && (map[maps].ACPI & 1) == 0) // ACPI 3.0 ignore
		{
			// ignore
			continue;
		}

		// print entry
		putnum(map[maps].baseH, 16, FG_WHITE);
		putnum(map[maps].baseL, 16, FG_WHITE);
		puts(" | ", FG_CYAN);
		putnum(map[maps].lenH, 16, FG_WHITE);
		putnum(map[maps].lenL, 16, FG_WHITE);
		puts(" | ", FG_CYAN);
		switch (map[maps].type)
		{
		case MEMORY_MAP_USABLE:
			puts(MEMORY_MAP_USABLE_MSG, FG_WHITE);
			break;
		case MEMORY_MAP_RESERVED:
			puts(MEMORY_MAP_RESERVED_MSG, FG_WHITE);
			break;
		case MEMORY_MAP_ACPI_RECLAIM:
			puts(MEMORY_MAP_ACPI_RECLAIM_MSG, FG_WHITE);
			break;
		case MEMORY_MAP_ACPI_NVS:
			puts(MEMORY_MAP_ACPI_NVS_MSG, FG_WHITE);
			break;
		case MEMORY_MAP_BAD:
			puts(MEMORY_MAP_BAD_MSG, FG_RED);
			break;
		default:
			puts(MEMORY_MAP_OTHER_MSG, FG_RED);
			break;
		}

		puts("\n", FG_CYAN);

		maps++;
	} while (cont != 0 && maps < MAX_MAP);

	return 0;
}
