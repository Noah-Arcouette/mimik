#include "main.h"
#include <string.h>
#include <endian.h>
#include <mio.h>

void
emitGaps (void)
{
	if (!outputGapsz) return;

	struct MiO s;
	s.magic = htole32(MIO_MAGIC);
	s.flags = 0;
	strncpy((char *)s.name, (char *)MIO_SPECIAL_MIO_GAPS, sizeof(s.name));
	s.size = htole64(sizeof(struct MiO_Gap)*outputGapsz);

	emit(&s, sizeof(s));
	emit(outputGap, sizeof(struct MiO_Gap)*outputGapsz);
}
