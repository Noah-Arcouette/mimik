#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>
#include <mio.h>

void
printEntry (FILE *fp, unsigned long long size)
{
	long off = ftell(fp);

	// read the entry information
	struct MiO_Entry entry;
	if (fread(&entry, sizeof(entry), 1, fp) != 1)
	{
		printf(gettext("\n\tFailed to read entry\n"));
		errors++;
		fseek(fp, off+size, SEEK_SET);
		return;
	}

	printf(gettext("\n\tEntry : %.*s\n"),
		(int)sizeof(entry.entry), entry.entry);

	// check if the size is different than sizeof(arch)
	if (sizeof(entry) != size)
	{
		printf(gettext(
			"\tError, entry data size mismatched with section size\n"));
		errors++;
		fseek(fp, off+size, SEEK_SET);
	}
}
