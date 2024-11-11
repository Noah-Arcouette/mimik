#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static struct context _ctx = {
	.var   = (struct variable *)NULL,
	.vars  = 0,
	.varcp = 0,

	.label   = (struct label *)NULL,
	.labels  = 0,
	.labelcp = 0,

	.parent = (struct context *)NULL
};
struct context *ctx = &_ctx;

void
pushContext (void)
{
	// allocate new context
	struct context *newCtx = (struct context *)malloc(sizeof(struct context));
	if (!newCtx)
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}

	// set to current
	memset(newCtx, 0, sizeof(struct context)); //nullify

	newCtx->parent = ctx;
	ctx            = newCtx;
}

int
popContext (void)
{
	if (!ctx->parent) // if there's no parent
	{
		fprintf(stderr, "%s:%zu: Error, attempting to pop from root context.\n", filename, lineno);
		return 1;
	}

	struct variable *v;
	struct variable *c; // parent, compared to, variable
	struct context  *parent = ctx->parent;
	size_t vars = ctx->vars;
	while (vars--) // go through all variables
	{
		v = &ctx->var[vars];

		// find variable in parent
		for (size_t i = 0; i<parent->vars; i++)
		{
			c = &parent->var[i];

			// are they same variable, and have different deltas
			if (!strcmp(c->name, v->name) && c->delta != v->delta)
			{
				fputc('\t', fout);
				printType(fout, c->type);

				// merge variables with a phi
				fprintf(fout, " %%%zu := %%%zu %%%zu\n", temps++, c->delta, v->delta);

				// set parent's delta
				c->delta = temps-1;
			}
		}
	}

	// free context
	freeCtx(ctx);

	// set tail as current
	ctx = parent;
	return 0;
}
