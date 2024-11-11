#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct variable *
defineVar (char *name, struct type t)
{
	struct variable *v;
	// check if variable exists
	if ((v = getVar(name))) // get variable
	{
		fprintf(stderr, "%s:%zu: Symbol `%s' already exists.\n", filename, lineno, name);
		fprintf(stderr, " -> first seem on line %zu in file `%s'.\n", v->lineno, v->filename);
		return (struct variable *)NULL; // already exists
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

	v->delta = 0; // no delta
	v->name  = name;
	memcpy(&v->type, &t, sizeof(struct type));

	// add line information
	v->filename = filename;
	v->lineno   = lineno;

	return v;
}

struct variable *
getVar (char *name)
{
	struct context *current = ctx;
	while (current) // until end contextes
	{
		// loop through all variables
		size_t i = current->vars;
		while (i--)
		{
			// found variable
			if (!strcmp(current->var[i].name, name))
			{
				struct variable *v = &current->var[i];

				// if not in current context
				if (current != ctx)
				{
					// pull into the current context, verbatim

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
							int errnum;
						memerror:
							errnum = errno;
							fprintf(stderr, "%s: Failed to allocate memory.\n", self);
							fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
							exit(1);
						}
					}

					// copy over the data
					memcpy(&ctx->var[ctx->vars-1], v, sizeof(struct variable));
					v = &ctx->var[ctx->vars-1];

					// duplicate the name
					v->name = strdup(v->name);
					if (!v->name)
					{
						goto memerror;
					}
				}

				return v;
			}
		}

		current = current->parent; // move up one context
	}
	return (struct variable *)NULL; // didn't find the variable
}
