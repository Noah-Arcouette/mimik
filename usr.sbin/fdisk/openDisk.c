#include "main.h"
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

FILE *disk      = NULL;
size_t diskSize = 0;

int
openDisk (int argc, char *argv[])
{
	// is it even there
	if (argc < 2)
	{
		fprintf(stderr, gettext("%s: No disk file provided\n"), self);
		return 1;
	}

	// get the name
	const char *path = argv[1];
	// open it
	disk = fopen(path, "w+");
	if (!disk)
	{
		fprintf(stderr,
			gettext("%s: Failed to open disk for writing and reading, %s\n"),
			self, strerror(errno));
		return 1;
	}

	// make sure you can seek into it
	if (fseek(disk, 0, SEEK_END) < 0)
	{
		fprintf(stderr, gettext("%s: Failed to seek into disk file, %s\n"),
			self, strerror(errno));
		fclose(disk);
		return 1;
	}
	diskSize = ftello(disk);
	rewind(disk);

	return 0;
}
