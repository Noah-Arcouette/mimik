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

	// call onto the parent
	if (c->parent)
	{
		_freeCtx(c->parent);
		free(c); // free ourselves if there is a parent,
			// so all but the last contex, _ctx, will be freed
	}
}

void
freeCtx (void)
{
	_freeCtx(ctx);
}
