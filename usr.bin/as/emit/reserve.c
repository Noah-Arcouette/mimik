#include "../emit.h"
#include "../main.h"
#include <libintl.h>
#include <endian.h>

long virtualOffset = 0;

void
reserve (long amt)
{
	if (!(symbolFlags & MIO_SYMBOL_FLAG_VIRTUAL))
	{
		prettyprint(gettext("Cannot reserve data in non-virtual section\n"));
		errors++;
		return;
	}

	// update symbols and sections
	if (currentSection >= 0)
	{
		struct MiO *section = (void *)&emitbuf[currentSection];
		size_t oldSize = le64toh(section->size);
		section->size  = htole64(oldSize+amt);
	}
	if (currentSymbol >= 0)
	{
		struct MiO_Symbol *s = &symbol[currentSymbol];
		size_t oldSize = le64toh(s->size);
		s->size        = htole64(oldSize+amt);
	}

	virtualOffset += amt;
}
