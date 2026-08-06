#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
mbr_commit (void)
{
	if (dryRun) return;

	mbr_updateCHS();
	if (!writeMBR || errors) return;

	if (fseek(disk, 0, SEEK_SET) < 0)
	{
		fprintf(stderr, gettext("%s: Failed to seek into disk, %s\n"),
			self, strerror(errno));
		errors++;
		return;
	}

	mayBeCorrupt = 1;
	if (fwrite(&mbr, sizeof(mbr), 1, disk) != 1)
	{
		fprintf(stderr, gettext("%s: Failed to write to disk, %s\n"),
			self, strerror(errno));
		errors++;
	}
}
