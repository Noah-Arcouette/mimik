#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>

void
relocateSymbols (void)
{
	for (long i = 0; i<symbols; i++)
	{
		struct MiO_Symbol *sym = &symbol[i];

		// skip literals
		int flags = le16toh(sym->flags);
		if (flags & MIO_SYMBOL_FLAG_LITERAL) continue;

		short symIsVirtual = 0;
		if (flags & MIO_SYMBOL_FLAG_VIRTUAL) symIsVirtual = 1;

		long symStart = le64toh(sym->value);

		short foundIt = 0;
		for (long j = 0; j<maps; j++)
		{
			struct MiO_Map *m = &map[j];

			// find the right map
			short mapIsVirtual = 0;
			if (m->flags & MIO_MAP_FLAG_VIRTUAL) mapIsVirtual = 1;

			// must both be virtual
			if (mapIsVirtual != symIsVirtual) continue;

			// check if its loaded from this map
			long mapStart = le64toh(m->from);
			long mapEnd   = le64toh(m->amount)+mapStart;

			if (symStart >= mapStart && symStart <= mapEnd)
			{
				symStart = symStart-mapStart+le64toh(m->virtual);
				foundIt  = 1;
				break;
			}
		}

		if (!foundIt)
		{
			fprintf(stderr, gettext("%s: Symbol `%.*s' was not loaded\n"),
				self, 256, sym->name);
			errors++;
		}

		sym->value = htole64(symStart);
	}
}
