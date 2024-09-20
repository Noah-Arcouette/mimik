#include <stdio.h>
#include "defs.h"

void
globalSymbol (const char *symbol)
{
	printf("Parser: Global symbol `%s'\n", symbol);
}
