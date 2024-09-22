#include <stdio.h>
#include <mio.h>
#include "defs.h"
#include <string.h>

void
globalSymbol (const char *symbol)
{
	// Find symbol
	struct symbol *currentSymbol = currentSection->firstSymbol;
	while (currentSymbol)
	{
		if (!strcmp(currentSymbol->name, symbol))
		{
			currentSymbol->flags |= MIO_SYMLIST_GLOBAL;

			goto good;
		}

		currentSymbol = currentSymbol->next;
	}

	// failed to find
	fprintf(stderr, "%s:%d: Failed to find symbol `%s' in current section.\n", filename, lineno-1, symbol);
good:
	// Tick global flag
	printf("Parser: Global symbol `%s'\n", symbol);
}
