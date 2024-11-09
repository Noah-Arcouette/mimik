#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int
defineVar (char *name, struct type t)
{
	struct variable *v;
	// check if variable exists
	if ((v = getVar(name))) // get variable
	{
		fprintf(stderr, "%s:%zu: Symbol `%s' already exists.\n", filename, lineno, name);
		fprintf(stderr, " -> first seem on line %zu in file `%s'.\n", v->lineno, v->filename);
		return 1; // already exists
	}

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
	v = &ctx->var[ctx->vars-1];

	v->delta = -1; // no delta
	v->name  = name;
	memcpy(&v->type, &t, sizeof(struct type));

	// add line information
	v->filename = filename;
	v->lineno   = lineno;

	return 0;
}

struct variable *
getVar (char *name)
{
	// loop through all variables
	size_t i = ctx->vars;
	while (i--)
	{
		if (!strcmp(ctx->var[i].name, name))
		{
			return &ctx->var[i]; // found variable
		}
	}
	return (struct variable *)NULL; // didn't find the variable
}
