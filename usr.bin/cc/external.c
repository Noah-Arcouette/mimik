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

    ctx->externals++; // increment amount of externals

    // if we need to grow it
    if (ctx->externals >= ctx->externalcp)
    {
        ctx->externalcp = (3*ctx->externals)/2; // grow by 3/2

        // reallocate
        ctx->external = (struct external *)realloc(ctx->external, ctx->externalcp*sizeof(struct external));
        if (!ctx->external) // if failed
        {
            ctx->externals  = 0;
            ctx->externalcp = 0;
            int errnum = errno;
            fprintf(stderr, "%s: Failed to allocate memory.\n", self);
            fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
            exit(1);
        }
    }

    // fill out information
    struct external *e = &ctx->external[ctx->externals-1]; // get the element
    memcpy(&e->type, &t, sizeof(struct type));
    e->name = name;
    return 0;
}
