#include "main.h"
#include <string.h>
#include <endian.h>
#include <mio.h>

void
emitMaps (void)
{
	if (!outputMaps) return;

	struct MiO s;
	s.magic = htole32(MIO_MAGIC);
	s.flags = 0;
	strncpy((char *)s.name, (char *)MIO_SPECIAL_MIO_MAPS, sizeof(s.name));
	s.size = htole64(sizeof(struct MiO_Map)*outputMaps);

	emit(&s, sizeof(s));
	emit(outputMap, sizeof(struct MiO_Map)*outputMaps);
}
