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
		symStart = relocate(symStart, symIsVirtual);

		if (symStart < 0)
		{
			fprintf(stderr, gettext("%s: Symbol `%.*s' was not loaded\n"),
				self, 256, sym->name);
			errors++;
		}

		sym->value = htole64(symStart);
	}
}
