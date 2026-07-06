#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void
resolveConflictSymbols (void)
{
	// for each input
	for (long i = 0; i<inputs; i++)
	{
		struct inputFile *firstInput = &input[i];

		// no symbols
		if (!firstInput->symbol) continue;

		// for each symbol
		for (long j = 0; j<firstInput->symbols; j++)
		{
			struct MiO_Symbol *firstSymbol = &firstInput->symbol[j];

			// for each other input
			for (long k = i+1; k<inputs; k++)
			{
				struct inputFile *secondInput = &input[k];

				// no symbols
				if (!secondInput->symbol) continue;

				// for each symbol
				for (long l = 0; l<secondInput->symbols; l++)
				{
					struct MiO_Symbol *secondSymbol = &secondInput->symbol[l];

					// not matching
					if (strncmp((char *)firstSymbol->name,
						(char *)secondSymbol->name,
						sizeof(firstSymbol->name)))
					{
						continue;
					}
					// else, matching

					if (le16toh(firstSymbol->flags) & MIO_SYMBOL_FLAG_GLOBAL)
					{
						// crash
						fprintf(stderr, gettext(
						"%s: Global symbol `%s:%.*s' collides with `%s:%.*s'\n"
						),
							self,
							firstInput->path,
							(int)sizeof(firstSymbol->name),
							firstSymbol->name,
							secondInput->path,
							(int)sizeof(secondSymbol->name),
							secondSymbol->name);
						errors++;
						continue;
					}
					if (le16toh(secondSymbol->flags) & MIO_SYMBOL_FLAG_GLOBAL)
					{
						// crash
						fprintf(stderr, gettext(
						"%s: Global symbol `%s:%.*s' collides with `%s:%.*s'\n"
						),
							self,
							secondInput->path,
							(int)sizeof(secondSymbol->name),
							secondSymbol->name,
							firstInput->path,
							(int)sizeof(firstSymbol->name),
							firstSymbol->name);
						errors++;
						continue;
					}

					// get new name
					char name[256];

					// copy the old name
					char *tail = stpncpy(
						name,
						(char *)firstSymbol->name,
						sizeof(firstSymbol->name));

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

					char *oldname    = (char *)firstSymbol->name;
					size_t oldnamesz = sizeof(firstSymbol->name);

					// rename gaps
					if (secondInput->gap)
					{
						for (long n = 0; n<secondInput->gaps; n++)
						{
							if (strncmp((char *)secondInput->gap[n].symbol,
								oldname, oldnamesz))
							{
								continue;
							}

							// copy it
							strncpy((char *)secondInput->gap[n].symbol,
								name, oldnamesz);
						}
					}

					// rename symbol
					strncpy((char *)secondSymbol->name, name, oldnamesz);

					// try again
					l--;
				}
			}
		}
	}
}
