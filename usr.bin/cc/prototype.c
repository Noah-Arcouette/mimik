#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct prototype *
definePrototype (struct type t, char *name, int isExternal)
{
	// check for the symbol
	struct symbol sym;
	if (!getSymbol(name, &sym))
	{
		if (sym.type == SYMBOL_PROTOTYPE)
		{
			/*
			+------------------+-----------------+-----------------+
			| Know is external | New is external | Fail or Mirror? |
			+------------------+-----------------+-----------------+
			| Implemented(0)   | Implemented     | Fail            | -> Two implementations
			| Implemented      | External(1)     | Mirror          | -> Check if external matches the implementation
			| External         | Implemented     | Mirror          | -> Check if implementation matches the external
			| External         | External        | Mirror          | -> Check if external matches the other external
			+------------------+-----------------+-----------------+

			This is a logic NOR, hence    |
                                          |
									      v
			*/
			if (!(sym.prototype->isExternal || isExternal)) // if fail/implemented twice
			{
				fprintf(stderr, "%s:%zu: Function `%s' is implemented twice\n", filename, lineno, name);
				goto first_seen_and_error;
			}
			// else
			// check if return type matches
			if (!compareType(sym.prototype->returnType, t))
			{
				fprintf(stderr, "%s:%zu: Function does not match previous return type.\n", filename, lineno);
				goto first_seen_and_error;
			}

			sym.prototype->isMirroring          = 1; // setup mirroring
			sym.prototype->mirroring.parameters = 0;
			sym.prototype->mirroring.lineno     = lineno;
			sym.prototype->mirroring.filename   = filename;

			free(name);
			freeType(t);
			return sym.prototype; // return in mirroring mode
		}

		fprintf(stderr, "%s:%zu: Failed symbol `%s' already exists\n", filename, lineno, name);
	first_seen_and_error:
		fprintf(stderr, " -> First seen on line %zu in file `%s'\n", sym.lineno, sym.filename);

		return (struct prototype *)NULL;
	}
	// else, new prototype

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

	p->filename   = filename;
	p->lineno     = lineno;
	p->isExternal = isExternal;

	return p;
}

void
freePrototype (struct prototype *p)
{
	if (p->isMirroring) // if mirroring
	{
		p->isMirroring = 0; // close mirroring

		return;
	}
	// else

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

int
doneWithPrototype (struct prototype *p)
{
	// if mirroring
	if (p->isMirroring)
	{
		if (p->parameters > p->mirroring.parameters)
		{
			// check for variable underflow
			fprintf(stderr, "%s:%zu: Function mismatch insufficient amount of parameter, in function `%s'.\n", filename, lineno, p->name);
			fprintf(stderr, " -> Current definition on line %zu in file `%s'\n", p->lineno, p->filename);
			fprintf(stderr, " -> New definition on line %zu in file `%s'\n", p->mirroring.lineno, p->mirroring.filename);

			return 1; // it is not okay
		}

		// close mirroring
		p->isMirroring = 0;

		// set the new current definition
		p->lineno   = p->mirroring.lineno;
		p->filename = p->mirroring.filename;

		return 0;
	}
	// else

	// resize
	p->parameter = (struct parameter *)realloc(p->parameter, p->parameters*sizeof(struct parameter));
	if (!p->parameter) // failed, although this will never happen since we should only be deallocating memory
	{
		int errnum = errno;
		fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
		fprintf(stderr, " -> Warning %d: %s.\n", errnum, strerror(errnum));
		return 0; // it's still okay
		// just don't update the capacity
	}

	// update capacity information
	p->parametercp = p->parameters;

	return 0;
}
