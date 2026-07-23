#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void
checkGlobalSymbols (void)
{
	// for each input
	for (long i = 0; i<inputs; i++)
	{
		struct inputFile *firstFile = &input[i];

		// no symbols
		if (!firstFile->symbol) continue;

		// for each symbol
		for (long j = 0; j<firstFile->symbols; j++)
		{
			struct MiO_Symbol *firstSymbol = &firstFile->symbol[j];

			// only globals
			if (!(le16toh(firstSymbol->flags) & MIO_SYMBOL_FLAG_GLOBAL))
			{
				continue;
			}

			// for each other input
			for (long k = i+1; k<inputs; k++)
			{
				struct inputFile *secondFile = &input[k];

				// no symbols
				if (!secondFile->symbol) continue;

				// for each symbol
				for (long l = 0; l<secondFile->symbols; l++)
				{
					struct MiO_Symbol *secondSymbol = &secondFile->symbol[l];

					// only global symbols
					if (!(le16toh(secondSymbol->flags) &
						MIO_SYMBOL_FLAG_GLOBAL))
					{
						continue;
					}

					// check if they match
					if (!strncmp(
						(char *)firstSymbol->name,
						(char *)secondSymbol->name,
						sizeof(firstSymbol->name)))
					{
						fprintf(stderr, gettext(
							"%s: Symbol `%s:%s' conflicts with `%s:%s'\n"),
							self,
							firstFile->path, firstSymbol->name,
							secondFile->path, secondSymbol->name);
						errors++;
					}
				}
			}
		}
	}
}
