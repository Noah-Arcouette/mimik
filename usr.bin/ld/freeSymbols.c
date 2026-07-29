#include "main.h"
#include <stdlib.h>

void
freeSymbols (void)
{
	outputSymbolsz = 0;
	outputSymbolcp = 0;
	free(outputSymbol);
	outputSymbol = NULL;
}
