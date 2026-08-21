#include "../emit.h"
#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int  symbolFlags   = 0;
long currentSymbol = -1;

struct MiO_Symbol *symbol  = NULL;
size_t             symbols = 0;

void
emitSymbol (const wchar_t *name)
{
	if (currentSection < 0)
	{
		prettyprint(gettext("Cannot create symbol outside of a section\n"));
		errors++;
		return;
	}

	// check name length
	if ((wcstombs(NULL, name, 0)-1) > 256)
	{
		prettyprint(gettext("Symbol name is too large\n"));
		errors++;
		return;
	}

	// allocate a new symbol
	symbols++;
	void *buf = realloc(symbol, sizeof(struct MiO_Symbol)*symbols);
	if (!buf)
	{
		symbols--;
		int error = errno;
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(error));
		errors++;
		return;
	}
	symbol = buf;

	currentSymbol = symbols-1;

	struct MiO_Symbol *s = &symbol[symbols-1];

	memset(s, 0, sizeof(struct MiO_Symbol));
	wcstombs((void *)s->name, name, 256);
	s->size  = 0;
	s->flags = htole16(symbolFlags);
	if (symbolFlags & MIO_SYMBOL_FLAG_VIRTUAL)
	{
		s->value = htole64(virtualOffset);
	}
	else
	{
		s->value = htole64(emitsz);
	}
}

void
emitSymbolData (void)
{
	emitSection(MIO_SPECIAL_MIO_SYMBOLS_W);
	emit(symbol, symbols*sizeof(struct MiO_Symbol));

	free(symbol);
	symbol  = NULL;
	symbols = 0;
	currentSymbol = -1;
}
