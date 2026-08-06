#include "main.h"
#include <sys/stat.h>
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
setBootCode (const char *path)
{
	struct stat statbuf;
	if (stat(path, &statbuf))
	{
		fprintf(stderr, gettext("%s: Failed to stat file `%s', %s\n"),
			self, path, strerror(errno));
		errors++;
		return;
	}

	// get the size
	size_t size = statbuf.st_size;
	if (!size)
	{
		fprintf(stderr, gettext("%s: Boot code, `%s', has a size of zero\n"),
			self, path);
		errors++;
		return;
	}

	switch (partMode)
	{
	case MODE_NONE:
		fprintf(stderr,
			gettext("%s: No partition map selected for boot code\n"), self);
		errors++;
		break;
	case MODE_MBR:
	#ifdef MBR
		mbr_setBootCode(path, size);
	#endif
		break;
	}
}
