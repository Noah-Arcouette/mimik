#include "main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <mio.h>

void
emitArchSection (void)
{
	struct MiO s;
	s.magic = htole32(MIO_MAGIC);
	s.flags = 0;
	strncpy((char *)s.name, (char *)MIO_SPECIAL_MIO_ARCH, sizeof(s.name));
	s.size = htole64(sizeof(outputArch));

	emit(&s, sizeof(s));
	emit(&outputArch, sizeof(outputArch));
}
