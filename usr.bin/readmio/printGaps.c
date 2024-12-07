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
printGaps (FILE *fp, struct MiO_Section s)
{
	uint64_t off  = le64toh(*(uint64_t *)s.offset);
	uint64_t size = le64toh(*(uint64_t *)s.size);

	long initOff = ftell(fp); // save initial offset
	fseek(fp, dataStart+off, SEEK_SET); // goto the start

	struct MiO_Gap entry;
	ssize_t entries = size/sizeof(entry); // amount of entries

	while (entries--)
	{
		if (fread(&entry, sizeof(entry), 1, fp) != 1)
		{
			printError(errno, "Failed to read gaps entry from section.\n");
			return;
		}

		printf("\n\tName:  `%.*s'\n", (int)sizeof(entry.name), entry.name);
		printf("\tOffset: %ld\n", le64toh(*(uint64_t *)s.offset));
		printf("\tFlags:  ");
		if (entry.type & MIO_GAP_FLAG_READ)
		{
			printf("Reading ");
		}
		if (entry.type & MIO_GAP_FLAG_WRITE)
		{
			printf("Writing ");
		}
		if (entry.type & MIO_GAP_FLAG_EXECUTE)
		{
			printf("Executing ");
		}
		switch (entry.type & MIO_GAP_TYPE_MASK)
		{
		case MIO_GAP_ABSOLUTE_BYTE:
			printf("Absolute-Byte\n");
			break;
		case MIO_GAP_ABSOLUTE_WORD:
			printf("Absolute-Word\n");
			break;
		case MIO_GAP_ABSOLUTE_DWORD:
			printf("Absolute-DWord\n");
			break;
		case MIO_GAP_ABSOLUTE_QWORD:
			printf("Absolute-QWord\n");
			break;
		case MIO_GAP_RELATIVE_BYTE:
			printf("Relative-Byte\n");
			break;
		case MIO_GAP_RELATIVE_WORD:
			printf("Relative-Word\n");
			break;
		case MIO_GAP_RELATIVE_DWORD:
			printf("Relative-DWord\n");
			break;
		case MIO_GAP_RELATIVE_QWORD:
			printf("Relative-QWord\n");
			break;
		default:
			printf("(unrecognized)\n");
			break;
		}
	}

	fseek(fp, initOff, SEEK_SET); // restore offset
}
