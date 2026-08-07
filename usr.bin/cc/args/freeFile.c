#include "../args.h"
#include <stdlib.h>
#include <stdio.h>

void
args_freeFile (void)
{
	for (long i = 0; i<args_files; i++)
	{
		struct args_file *file = &args_file[i];

		free(file->path);
		if (file->fp) fclose(file->fp);
	}

	free(args_file);
	args_file  = NULL;
	args_files = 0;
}
