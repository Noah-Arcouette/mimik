#include <sys/types.h>
#include <mio-x86.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "defs.h"

void
printSeg (FILE *fp, struct MiO_Section s)
{
	uint64_t off  = le64toh(*(uint64_t *)s.offset);
	uint64_t size = le64toh(*(uint64_t *)s.size);

	long initOff = ftell(fp); // save initial offset
	fseek(fp, dataStart+off, SEEK_SET); // goto the start

	struct MiO_Seg entry;
	ssize_t entries = size/sizeof(entry); // amount of entries

	while (entries--)
	{
		if (fread(&entry, sizeof(entry), 1, fp) != 1)
		{
			printError(errno, "Failed to read segment entry from section.\n");
			return;
		}

		printf("\tFlags:  ");
		if (entry.flags & MIO_SEG_FLAG_BSS)
		{
			printf("Uninitialized-Data-Segment ");
		}
		if (entry.flags & MIO_SEG_FLAG_READ)
		{
			printf("Readable ");
		}
		if (entry.flags & MIO_SEG_FLAG_WRITE)
		{
			printf("Writable ");
		}
		if (entry.flags & MIO_SEG_FLAG_EXECUTE)
		{
			printf("Executable");
		}
		printf("\n\tOffset:       %lu\n", (uint64_t)le64toh(*(uint64_t *)entry.offset));
		printf("\tData In-Situ: %lu\n",   (uint64_t)le64toh(*(uint64_t *)entry.fsize));
		printf("\tSegment:      ");

		if (currentHeader.arch == MIO_ARCH_X86)
		{
			switch (entry.segment)
			{
			case MIO_SEG_ES:
				printf("ES\n");
				break;
			case MIO_SEG_CS:
				printf("CS\n");
				break;
			case MIO_SEG_SS:
				printf("SS\n");
				break;
			case MIO_SEG_DS:
				printf("DS\n");
				break;
			case MIO_SEG_FS:
				if (currentHeader.uarch >= MIO_UARCH_I386)
				{
					printf("FS\n");
					break;
				}
			case MIO_SEG_GS:
				if (currentHeader.uarch >= MIO_UARCH_I386)
				{
					printf("GS\n");
					break;
				}
			default:
				printf("(unrecognized)\n");
				break;
			}
		}
		else
		{
			printf("(unrecognized)\n");
		}

		printf("\tPhysical:     %lu\n", (uint64_t)le64toh(*(uint64_t *)entry.physical));
		printf("\tAlignment:    %lu\n", (uint64_t)le64toh(*(uint64_t *)entry.align));
		printf("\tSize:         %lu\n", (uint64_t)le64toh(*(uint64_t *)entry.size));
	}

	fseek(fp, initOff, SEEK_SET); // restore offset
}
