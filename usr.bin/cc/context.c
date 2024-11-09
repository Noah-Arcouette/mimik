#include "defs.h"

static struct context _ctx = {
	.var   = (struct variable *)NULL,
	.vars  = 0,
	.varcp = 0
};
struct context *ctx = &_ctx;
