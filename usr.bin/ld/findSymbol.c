#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "main.h"

struct MiO_Symbol *
findSymbol (const wchar_t *w_name)
{
	char name[256];
	if (wcstombs(name, w_name, 256) < 0)
	{
		fprintf(stderr, gettext("%s: Failure converting `%S', %s\n"),
			self, w_name, strerror(errno));
		errors++;
		return NULL;
	}

	// check the output symbols fist
	for (size_t i = 0; i<outputSymbolsz; i++)
	{
		struct MiO_Symbol *sym = &outputSymbol[i];
		// symbol found
		if (!strncmp((char *)sym->name, name, sizeof(sym->name)))
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
			struct MiO_Symbol *symbol = &file->symbol[j];

			if (!strncmp((char *)symbol->name, name, sizeof(symbol->name)))
			{
				return symbol;
			}
		}
	}
	return NULL;
}
