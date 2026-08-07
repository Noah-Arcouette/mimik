#include "../args.h"
#include <stdlib.h>

void
args_freeInclude (void)
{
	args_system_includes = 0;

	args_includes = 0;
	free(args_include);
	args_include = NULL;
}
