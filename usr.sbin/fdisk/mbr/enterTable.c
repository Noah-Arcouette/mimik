#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>
#include <mbr.h>

struct mbr mbr;
int writeMBR = 0;

void
mbr_enterTable (int load)
{
	if (load)
	{
		if (fseek(disk, 0, SEEK_SET) < 0)
		{
			fprintf(stderr, gettext("%s: Failed to seek, %s\n"), self,
				strerror(errno));
			errors++;
			return;
		}

		if (fread(&mbr, sizeof(mbr), 1, disk) != 1)
		{
			fprintf(stderr, gettext("%s: Failed to read, %s\n"), self,
				strerror(errno));
			errors++;
			return;
		}
	}
	else
	{
		memset(&mbr, 0, sizeof(mbr));
		mbr.id = rand();
	}
	mbr.magic = htole16(MBR_MAGIC); // fix magic just in-case
	writeMBR = 1;
}
