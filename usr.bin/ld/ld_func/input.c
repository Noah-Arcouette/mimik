#include <stdio.h>
#include <errno.h>
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
	fclose(fp);
	}
