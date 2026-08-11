#include "../args.h"
#include "../main.h"
#include <stdlib.h>
#include <stdio.h>

void
args_freeFiles (void)
{
	for (int i = 0; i<args_files; i++)
	{
		FILE *fp = args_file[i].fp;
		if (fp) fclose(fp);
	}
	free(args_file);

	args_file  = NULL;
	args_files = 0;
}
