#include "../args.h"
#include <unistd.h>
#include <stdlib.h>

void
args_freeIncludes (void)
{
	free(args_include);
	args_include  = NULL;
	args_includes = 0;
}
