#include "defs.h"
#include <string.h>

int
getSymbol (const char *restrict name, struct symbol *restrict s)
{
	struct context *current = ctx;
	while (current) // for all contexts
	{
		// try to find the external
		for (size_t i = 0; i<current->externals; i++)
		{
			// skip un-named/unexistant variables
			if (!current->external[i].name)
			{
				continue;
			}

			if (!strcmp(current->external[i].name, name)) // check name
			{
				// found the symbol
				s->type     = SYMBOL_EXTERNAL;
				s->external = &current->external[i];

				s->lineno   = current->external[i].lineno;
				s->filename = current->external[i].filename;
				s->name     = current->external[i].name;
				return 0;
			}
		}

		// try to find the prototype
		for (size_t i = 0; i<current->prototypes; i++)
		{
			// skip un-named/unexistant prototypes
			if (!current->prototype[i].name)
			{
				continue;
			}

			if (!strcmp(current->prototype[i].name, name)) // check name
			{
				// found the symbol
				s->type      = SYMBOL_PROTOTYPE;
				s->prototype = &current->prototype[i];

				s->lineno   = current->prototype[i].lineno;
				s->filename = current->prototype[i].filename;
				s->name     = current->prototype[i].name;
				return 0;
			}
		}

		// try to find the variable
		for (size_t i = 0; i<current->variables; i++)
		{
			// skip un-named/unexistant variables
			if (!current->variable[i].name)
			{
				continue;
			}

			if (!strcmp(current->variable[i].name, name)) // check name
			{
				// found the symbol
				s->type     = SYMBOL_VARIABLE;
				s->variable = &current->variable[i];

				s->lineno   = current->variable[i].lineno;
				s->filename = current->variable[i].filename;
				s->name     = current->variable[i].name;
				return 0;
			}
		}

		current = current->parent; // next context
	}

    // symbol doesn't exist
    return 1;
}
