#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static struct context _ctx = {
	.var   = (struct variable *)NULL,
	.vars  = 0,
	.varcp = 0,

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

/*

pop context:
	check for conflicting variable deltas
		merge them with a phi node
	free context
	set tail as current

*/
