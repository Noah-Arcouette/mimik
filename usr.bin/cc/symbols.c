#include "defs.h"
#include <string.h>

int
getSymbol (const char *restrict name, struct symbol *restrict s)
{
    // try to find the external
    for (size_t i = 0; i<ctx->externals; i++)
    {
		// skip un-named/unexistant variables
		if (!ctx->external[i].name)
		{
			continue;
		}

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

	// try to find the prototype
	for (size_t i = 0; i<ctx->prototypes; i++)
	{
		// skip un-named/unexistant prototypes
		if (!ctx->prototype[i].name)
		{
			continue;
		}

		if (!strcmp(ctx->prototype[i].name, name)) // check name
		{
			// found the symbol
			s->type      = SYMBOL_PROTOTYPE;
			s->prototype = &ctx->prototype[i];

			s->lineno   = ctx->prototype[i].lineno;
			s->filename = ctx->prototype[i].filename;
			return 0;
		}
	}

    // symbol doesn't exist
    return 1;
}
