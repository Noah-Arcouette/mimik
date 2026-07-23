#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

struct MiO_Symbol *
findSymbol (const char *name)
{
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
