#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct prototype *
definePrototype (struct type t, char *name)
{
	// check for the symbol
	struct symbol sym;
	if (!getSymbol(name, &sym))
	{
		fprintf(stderr, "%s:%zu: Failed symbol `%s' already exists\n", filename, lineno, name);
		fprintf(stderr, " -> First seen on line %zu in file `%s'\n", sym.lineno, sym.filename);
		return (struct prototype *)NULL;
	}

	// allocate for the prototype
	ctx->prototypes++;
	if (ctx->prototypes >= ctx->prototypecp)
	{
		ctx->prototypecp = (3*ctx->prototypes)/2; // grow by 3/2

		// reallocate
		struct prototype *old = ctx->prototype; // save
		ctx->prototype = (struct prototype *)realloc(ctx->prototype, ctx->prototypecp*sizeof(struct prototype));
		if (!ctx->prototype) // failed to allocate
		{
			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));

			ctx->prototypes--;
			ctx->prototypecp = ctx->prototypes;
			ctx->prototype   = old; // restore
			return (struct prototype *)NULL; // soft fail
		}
	}

	// fill out information
	struct prototype *p = &ctx->prototype[ctx->prototypes-1];

	memset(p, 0, sizeof(struct prototype)); // fill out with null
	p->name = name;
	memcpy(&p->returnType, &t, sizeof(struct type));

	p->filename = filename;
	p->lineno   = lineno;

	return p;
}

void
freePrototype (struct prototype *p)
{
	free(p->name);
	freeType(p->returnType);
	while (p->parameters--)
	{
		freeParameter(&p->parameter[p->parameters]);
	}
	free(p->parameter);

	// nullify
	memset(p, 0, sizeof(struct prototype));
}

void
doneWithPrototype (struct prototype *p)
{
	// resize
	p->parameter = (struct parameter *)realloc(p->parameter, p->parameters*sizeof(struct parameter));
	if (!p->parameter) // failed, although this will never happen since we should only be deallocating memory
	{
		int errnum = errno;
		fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
		fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
		return;
	}

	// update capacity information
	p->parametercp = p->parameters;
}
