#include "defs.h"
#include <stdlib.h>

static void
_freeCtx (struct context *c)
{
	// free all variables
	while (c->vars--)
	{
		free(c->var[c->vars].name);
	}
	free(c->var);
}

void
freeCtx (void)
{
	_freeCtx(ctx);
}
