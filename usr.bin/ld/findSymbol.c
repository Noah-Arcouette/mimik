#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

struct MiO_Symbol *
findSymbol (const char *name)
{
	// check the output symbols fist
	for (size_t i = 0; i<outputSymbolsz; i++)
	{
		struct MiO_Symbol *sym = &outputSymbol[i];
		// symbol found
		if (strncmp((char *)sym->name, name, sizeof(sym->name)))
		{
			return sym;
		}
	}

	// for each input
	for (long i = 0; i<inputs; i++)
	{
		struct inputFile *file = &input[i];

		// no symbols
		if (!file->symbol) continue;

		// for each symbol
		for (long j = 0; j<file->symbols; j++)
		{
			struct MiO_Symbol *symbol = &input->symbol[j];

			if (!strncmp((char *)symbol->name, name, sizeof(symbol->name)))
			{
				return symbol;
			}
		}
	}
	return NULL;
}
