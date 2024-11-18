#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct variable *
defineVariable (char *name, struct type t)
{
	// try to find symbol
	struct symbol sym;
	if (!getSymbol(name, &sym))
	{
		fprintf(stderr, "%s:%zu: Local variable, `%s' already exists in scope.\n", filename, lineno, name);
		fprintf(stderr, " -> First seen on line %zu in file `%s'.\n", sym.lineno, sym.filename);
		return (struct variable *)NULL;
	}

	// allocate
	ctx->variables++;
	if (ctx->variables >= ctx->variablecp)
	{
		ctx->variablecp = (3*ctx->variables)/2; // grow by 3/2

		// reallocate
		struct variable *old = ctx->variable;
		ctx->variable = (struct variable *)realloc(ctx->variable, ctx->variablecp*sizeof(struct variable));
		if (!ctx->variable) // failed
		{
			// restore
			ctx->variable = old;
			ctx->variables--;
			ctx->variablecp = ctx->variables;

			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate memory for local variable, `%s'.\n", filename, lineno, name);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
			return (struct variable *)NULL;
		}
	}

	// fillout information
	struct variable *v = &ctx->variable[ctx->variables-1];

	v->name     = name;
	v->lineno   = lineno;
	v->filename = filename;
	v->delta    = 0;
	memcpy(&v->type, &t, sizeof(struct type));

	return v;
}

void
freeVariable (struct variable *v)
{
	free(v->name);
	freeType(v->type);

	// nullify
	memset(v, 0, sizeof(struct variable));
}

