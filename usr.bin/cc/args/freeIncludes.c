#include "../args.h"
#include <unistd.h>
#include <stdlib.h>

void
args_freeIncludes (void)
{
	for (int i = 0; i<args_includes; i++)
	{
		struct args_include *inc = &args_include[i];

		close(inc->fd);
	}
	free(args_include);
	args_include  = NULL;
	args_includes = 0;
}
