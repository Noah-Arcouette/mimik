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

		if (!definition())
		{
			continue;
		}

		fprintf(stderr, "%s:%zu: Unexpected token at root.\n", filename, lineno);
		return 1;
	}
	return 0;
}
