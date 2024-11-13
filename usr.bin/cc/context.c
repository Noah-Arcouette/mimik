#include "defs.h"
#include <string.h>
#include <stdlib.h>

static struct context _ctx = {
    .external   = (struct external *)NULL,
    .externals  = 0,
    .externalcp = 0,

	.prototype   = (struct prototype *)NULL,
	.prototypes  = 0,
	.prototypecp = 0
};
struct context *ctx = &_ctx;

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

    // nullify everything
    memset(ctx, 0, sizeof(struct context));
}

void
freeContexts (void)
{
    freeContext(ctx); // free the root context
}
