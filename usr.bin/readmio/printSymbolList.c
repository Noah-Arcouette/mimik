#include <sys/types.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "defs.h"

void
printSymbolList (FILE *fp, struct MiO_Section s)
{
	uint64_t off  = le64toh(*(uint64_t *)s.offset);
	uint64_t size = le64toh(*(uint64_t *)s.size);

	long initOff = ftell(fp); // save initial offset
	fseek(fp, dataStart+off, SEEK_SET); // goto the start

	struct MiO_SymList entry;
	ssize_t entries = size/sizeof(entry); // amount of entries

	while (entries--)
	{
		if (fread(&entry, sizeof(entry), 1, fp) != 1)
		{
			printError(errno, "Failed to read symbol list entry from section.\n");
			return;
		}

		printf("\n\tName: `%.*s'\n", (int)sizeof(entry.name), entry.name);
		printf("\tSize:  %lu\n", le64toh(*(uint64_t *)entry.size));
		printf("\tValue: %lu\n", le64toh(*(uint64_t *)entry.val));

		printf("\tFlags: ");
		switch (entry.flags & MIO_SYMLIST_TYPE_MASK)
		{
		case MIO_SYMLIST_TYPE_ABSOLUTE:
			printf("Absolute ");
			break;
		case MIO_SYMLIST_TYPE_BSS:
			printf("Uninitialized-Data ");
			break;
		case MIO_SYMLIST_TYPE_ADDRESS:
			printf("Address ");
			break;
		case MIO_SYMLIST_TYPE_FILE:
			printf("File-Declaration ");
			break;
		default:
			printf("(unrecognized-type) ");
			break;
		}
		if (entry.flags & MIO_SYMLIST_GLOBAL)
		{
			printf("Global");
		}
		printf("\n");
	}

	fseek(fp, initOff, SEEK_SET); // restore offset
}
