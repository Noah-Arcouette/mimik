#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int
defineVar (char *name, struct type t)
{
	// check if variable exists
	// if (getVar(name)) // get variable
	// {
		// return 1; // already exists
	// }

	// grow variable vector array
	ctx->vars++;
	if (ctx->vars > ctx->varcp)
	{
		ctx->varcp = (3*ctx->vars)/2; // grow by 3/2

		// reallocate
		ctx->var = (struct variable *)realloc(ctx->var, sizeof(struct variable)*ctx->varcp);

		if (!ctx->var)
		{
			// clean up the rest
			ctx->vars  = 0;
			ctx->varcp = 0;
			free(name);

			int errnum = errno;
			fprintf(stderr, "%s: Failed to allocate memory.\n", self);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
			exit(1);
		}
	}

	// add variable
	size_t i = ctx->vars-1;
	ctx->var[i].delta = -1; // no delta
	ctx->var[i].name  = name;
	memcpy(&ctx->var[i].type, &t, sizeof(struct type));

	return 0;
}
