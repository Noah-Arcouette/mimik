#include "main.h"
#include <string.h>
#include <endian.h>
#include <mio.h>

void
emitSymbols (void)
{
	if (!outputSymbolsz) return;

	struct MiO s;
	s.magic = htole32(MIO_MAGIC);
	s.flags = 0;
	strncpy((char *)s.name, (char *)MIO_SPECIAL_MIO_SYMBOLS, sizeof(s.name));
	s.size = htole64(sizeof(struct MiO_Symbol)*outputSymbolsz);

	emit(&s, sizeof(s));
	emit(outputSymbol, sizeof(struct MiO_Symbol)*outputSymbolsz);
}
