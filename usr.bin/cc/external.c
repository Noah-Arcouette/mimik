#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
freeExternal (struct external *e)
{
    free(e->name); // free the name
    freeType(e->type); // free the type
    memset(e, 0, sizeof(struct external)); // nullify
}

int
defineExternal (char *name, struct type t)
{
    // TODO: need to check if the symbol is already defined anywhere
    struct symbol sym;
    if (!getSymbol(name, &sym))
    {
        fprintf(stderr, "%s:%zu: Error symbol `%s' already exists.\n", filename, lineno, name);
        fprintf(stderr, " -> First seen on line %zu in file `%s'\n", sym.lineno, sym.filename);
        return 1;
    }

    ctx->externals++; // increment amount of externals

    // if we need to grow it
    if (ctx->externals >= ctx->externalcp)
    {
        ctx->externalcp = (3*ctx->externals)/2; // grow by 3/2

        // reallocate
		struct external *old = ctx->external; // save
        ctx->external = (struct external *)realloc(ctx->external, ctx->externalcp*sizeof(struct external));
        if (!ctx->external) // if failed
        {
			// restore
            ctx->externals--;
            ctx->externalcp = ctx->externals;
			ctx->external   = old;

            int errnum = errno;
            fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
            fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
            return 1;
        }
    }

    // fill out information
    struct external *e = &ctx->external[ctx->externals-1]; // get the element
    memcpy(&e->type, &t, sizeof(struct type));
    e->name     = name;
    e->filename = filename;
    e->lineno   = lineno;
    return 0;
}
