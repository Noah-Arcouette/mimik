#include "defs.h"
#include <stdlib.h>

void
freeCtx (struct context *c)
{
	// free all variables
	while (c->vars--)
	{
		free(c->var[c->vars].name);
	}
	free(c->var);

	// free all labels
	while (c->labels--)
	{
		free(c->label[c->labels].name);
	}
	free(c->label);

	if (c->parent) // if parent then free the context
		free(c);
}

void
freeAllContexts (void)
{
	struct context *c = ctx;
	struct context *parent;
	while (c) // look ahead, so the last context doesn't get freed
	{
		parent = c->parent;
		freeCtx(c); // free context's data
		c = parent; // move up one
	}
}
