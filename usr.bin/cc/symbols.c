#include "defs.h"
#include <string.h>

int
getSymbol (const char *restrict name, struct symbol *restrict s)
{
    // try to find the external
    for (size_t i = 0; i<ctx->externals; i++)
    {
        if (!strcmp(ctx->external[i].name, name)) // check name
        {
            // found the symbol
            s->type     = SYMBOL_EXTERNAL;
            s->external = &ctx->external[i];

            s->lineno   = ctx->external[i].lineno;
            s->filename = ctx->external[i].filename;
            return 0;
        }
    }

    // symbol doesn't exist
    return 1;
}