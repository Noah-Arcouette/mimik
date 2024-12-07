#include <sys/types.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "defs.h"

void
printLibraries (FILE *fp, struct MiO_Section s)
{
	uint64_t off  = le64toh(*(uint64_t *)s.offset);
	uint64_t size = le64toh(*(uint64_t *)s.size);

	long initOff = ftell(fp); // save initial offset
	fseek(fp, dataStart+off, SEEK_SET); // goto the start

	struct MiO_Lib entry;
	ssize_t entries = size/sizeof(entry); // amount of entries

	while (entries--)
	{
		if (fread(&entry, sizeof(entry), 1, fp) != 1)
		{
			printError(errno, "Failed to read library entry from section.\n");
			return;
		}

		printf("\tFile: `%.*s'\n", (int)sizeof(entry.path), entry.path);
		printf("\tType: ");
		switch (entry.type)
		{
		case MIO_LIB_TYPE_NEEDED:
			printf("Needed\n");
			break;
		case MIO_LIB_TYPE_OPTIONAL:
			printf("Optional\n");
			break;
		default:
			printf("(unrecognized)\n");
			break;
		}
	}

	fseek(fp, initOff, SEEK_SET); // restore offset
}
