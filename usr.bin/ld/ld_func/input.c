#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "../defs.h"

void
ld_input (const char *file)
{
	FILE *fp = fopen(file, "r");
	if (!fp)
	{
		error(errno, "Failed to open file `%s' for reading\n", file);
		return;
	}

	// read the header
	struct MiO_Header h;
	if (fread(&h, sizeof(struct MiO_Header), 1, fp) != 1)
	{
		error(errno, "%s: Failed to read header\n", file);
		goto close_and_leave;
	}

	// validate the header
	if (memcmp(h.magic, MIO_MAGIC, sizeof(h.magic)))
	{
		error(0, "%s: Corrupt magic number\n", file);
		goto close_and_leave;
	}
	if (h.version != MIO_CURRENT_VERSION)
	{
		error(0, "%s: Unsupported format version\n", file);
		goto close_and_leave;
	}
	if (!(h.flags & MIO_HEADER_FLAG_LAST))
	{
		error(0, "%s: FAT Binaries are not supported\n", file);
		goto close_and_leave;
	}
close_and_leave:
	fclose(fp);
	}
