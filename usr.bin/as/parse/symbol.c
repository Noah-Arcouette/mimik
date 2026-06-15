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
emitSymbol (const char *name)
{
	if (currentSection < 0)
	{
		prettyprint(gettext("Cannot create symbol outside of a section\n"));
		errors++;
		return;
	}

	// check name length
	if (strlen(name) > 256)
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
	strncpy((void *)s->name, name, sizeof(s->name));
	s->size  = 0;
	s->flags = htole16(symbolFlags);
	if (symbolFlags & MIO_SYMBOL_FLAG_VIRTUAL)
	{
		s->offset = htole64(virtualOffset);
	}
	else
	{
		s->offset = htole64(emitsz);
	}
}

void
emitSymbolData (void)
{
	emitSection((char *)MIO_SPECIAL_MIO_SYMBOLS);
	emit(symbol, symbols*sizeof(struct MiO_Symbol));

	free(symbol);
	symbol  = NULL;
	symbols = 0;
	currentSymbol = -1;
}
