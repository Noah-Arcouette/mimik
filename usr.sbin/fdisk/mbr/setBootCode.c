#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
mbr_setBootCode (const char *path, size_t size)
{
	if (size > sizeof(mbr.bootcode))
	{
		fprintf(stderr,
			gettext("%s: MBR boot code, `%s', restricted to %zu bytes\n"),
			self, path, sizeof(mbr.bootcode));
		errors++;
		return;
	}

	// open the file
	FILE *fp = fopen(path, "r");
	if (!fp)
	{
		fprintf(stderr,
			gettext("%s: Failed to open file `%s' for reading, %s\n"),
			self, path, strerror(errno));
		errors++;
		return;
	}

	// clear the boot code
	memset(mbr.bootcode, 0, sizeof(mbr.bootcode));

	// read in boot code
	if (fread(mbr.bootcode, 1, size, fp) != size)
	{
		fprintf(stderr,
			gettext("%s: Failed to read from file `%s', %s\n"),
			self, path, strerror(errno));
		errors++;
	}

	fclose(fp);
}
