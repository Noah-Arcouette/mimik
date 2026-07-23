#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void
renameStaticSymbols (void)
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

			// only statics
			if (le16toh(symbol->flags) & MIO_SYMBOL_FLAG_GLOBAL) continue;

			// get new name
			char name[256];

			// copy the old name
			char *tail = stpncpy(
				name,
				(char *)symbol->name,
				sizeof(symbol->name));

			// find the right offset
			int offset = tail-name;
			if ((256-offset) < 16)
			{
				// try to preserve as much of the name as possible
				offset = 256-16;
			}

			// add period
			name[offset] = '.';
			offset++;

			// add random tail to it
			int m = 15;
			while (m)
			{
				name[offset] = (rand() % 24)+'a';
				m--;
				offset++;
			}
			name[offset] = '\0';

			char *oldname    = (char *)symbol->name;
			size_t oldnamesz = sizeof(symbol->name);

			// rename gaps
			if (file->gap)
			{
				for (long n = 0; n<file->gaps; n++)
				{
					if (strncmp((char *)file->gap[n].symbol,
						oldname, oldnamesz))
					{
						continue;
					}

					// copy it
					strncpy((char *)file->gap[n].symbol, name, oldnamesz);
				}
			}

			// try again
			if (findSymbol(name)) j--;

			// rename symbol
			strncpy((char *)symbol->name, name, oldnamesz);
		}
	}
}
