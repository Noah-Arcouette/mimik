#include "defs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct prototype *currentFunction = (struct prototype *)NULL;

static struct context _ctx = {
    .external   = (struct external *)NULL,
    .externals  = 0,
    .externalcp = 0,

	.prototype   = (struct prototype *)NULL,
	.prototypes  = 0,
	.prototypecp = 0,

	.variable   = (struct variable *)NULL,
	.variables  = 0,
	.variablecp = 0,

	.breakTo    = 0,
	.continueTo = 0,

	.var = 0, // not used normally

	.parent = (struct context *)NULL
};
struct context *ctx = &_ctx;

size_t ctxLabel = 1;

void
freeContext (struct context *ctx)
{
    while (ctx->externals--) // for each external
    {
        freeExternal(&ctx->external[ctx->externals]); // free it
    }
    free(ctx->external); // free the array

	while (ctx->prototypes--) // for each prototype
	{
		freePrototype(&ctx->prototype[ctx->prototypes]);
	}
	free(ctx->prototype);

	while (ctx->variables--) // for each variable
	{
		freeVariable(&ctx->variable[ctx->variables]);
	}
	free(ctx->variable);

	// free the parent
	if (ctx->parent)
	{
		freeContext(ctx->parent);
		free(ctx->parent);
	}

    // nullify everything
    memset(ctx, 0, sizeof(struct context));
}

void
freeContexts (void)
{
    freeContext(ctx); // free the root context
}

void
pushContext (void)
{
	struct context *new = (struct context *)malloc(sizeof(struct context));

	if (!new) // if failed to allocate
	{
		int errnum = errno;
		fprintf(stderr, "%s:%zu: Failed to allocate new context.\n", filename, lineno);
		fprintf(stderr, " -> Errno %d: %s.\n", errnum, strerror(errnum));
		return;
	}

	// nullify and set
	memset(new, 0, sizeof(struct context));
	new->parent = ctx;

	// just continue along with things
	new->breakTo    = ctx->breakTo;
	new->continueTo = ctx->continueTo;

	new->var = ctx->var+1;

	// push
	ctx = new;
}

void
popContext (void)
{
	if (!ctx->parent)
	{
		fprintf(stderr, "%s:%zu: Error attempting to pop from root context.\n", filename, lineno);
		return;
	}

	struct context *toFree = ctx; // save
	ctx = ctx->parent; // pop

	toFree->parent = (struct context *)NULL; // so we don't recurse

	freeContext(toFree); // free
	free(toFree);
}
