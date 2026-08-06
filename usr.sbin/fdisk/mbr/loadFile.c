#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <errno.h>

void
mbr_loadFile (const char *path, long size)
{
	if (partitionIndex > 3)
	{
		fprintf(stderr,
			gettext("%s: Refusing to load file into partition higher than 3\n"),
			self);
		errors++;
		return;
	}

	if (!size) return; // nothing to load

	struct mbr_part *p = &mbr.part[partitionIndex];

	// check size
	long partSize = le32toh(p->sectors)*bytesPerSector;
	if (size > partSize)
	{
		fprintf(stderr,
			gettext("%s: Refusing to grow partition #%d for file\n"),
			self, partitionIndex);
		errors++;
		return;
	}

	// resize partition
	partSize = size/bytesPerSector;
	if (size % bytesPerSector) partSize++; // always round up
	p->sectors = htole32(partSize);
	mbr_updateCHS();

	if (dryRun) return; // just return

	// seek
	long partStart = le32toh(p->firstLBA)*bytesPerSector;
	if (fseek(disk, partStart, SEEK_SET) < 0)
	{
		fprintf(stderr,
			gettext("%s: Failed to seek into disk, %s\n"),
			self, strerror(errno));
		errors++;
		return;
	}

	// open file
	FILE *fp = fopen(path, "r");
	if (!fp)
	{
		fprintf(stderr,
			gettext("%s: Failed to open file `%s' for reading, %s\n"),
			self, path, strerror(errno));
		errors++;
		return;
	}

	// read in file
	char buf[BUFSIZ];
	size_t amt;
	do
	{
		// read in
		amt = fread(buf, 1, BUFSIZ, fp);
		if (amt < BUFSIZ && ferror(fp))
		{
			fprintf(stderr, gettext("%s: Failed to read from file `%s', %s\n"),
				self, path, strerror(errno));
			errors++;
			break;
		}

		// write out
		mayBeCorrupt = 1;
		if (fwrite(buf, 1, amt, disk) != amt)
		{
			fprintf(stderr, gettext("%s: Failed to write to disk, %s\n"),
				self, strerror(errno));
			errors++;
			break;
		}
	} while (amt == BUFSIZ);

	fclose(fp);
}
