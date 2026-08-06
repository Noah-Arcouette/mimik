#include "main.h"
#include <sys/stat.h>
#include <libintl.h>
#include <stdio.h>

void
loadFile (const char *path)
{
	if (partitionIndex < 0)
	{
		fprintf(stderr,
			gettext("%s: Refusing to load file without selected partition\n"),
			self);
		errors++;
		return;
	}

	struct stat statbuf;
	if (stat(path, &statbuf))
	{
		fprintf(stderr, gettext("%s: Failed to stat file `%s'\n"), self, path);
		errors++;
		return;
	}

	switch (partMode)
	{
	case MODE_NONE:
		fprintf(stderr,
			gettext("%s: No partition map selected for file loading\n"), self);
		errors++;
		break;
	case MODE_MBR:
	#ifdef MBR
		mbr_loadFile(path, statbuf.st_size);
	#endif
		break;
	}
}
