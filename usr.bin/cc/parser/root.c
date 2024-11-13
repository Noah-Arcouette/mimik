#include "../defs.h"

int
root (void)
{
	while (token)
	{
		if (!extern_())
		{
			continue;
		}

		fprintf(stderr, "%s:%zu: Unexpected at root.\n", filename, lineno);
		return 1;
	}
	return 0;
}
