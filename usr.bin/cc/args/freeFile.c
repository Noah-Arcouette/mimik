#include "../args.h"
#include <stdlib.h>

void
args_freeFile (void)
{
	free(args_file);
	args_file  = NULL;
	args_files = 0;
}
