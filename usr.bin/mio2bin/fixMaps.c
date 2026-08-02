#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <limits.h>
#include <stdio.h>

void
fixMaps (void)
{
	// find the largest set address
	long lastVirtual  = 0;
	long firstVirtual = LONG_MAX;
	for (long i = 0; i<maps; i++)
	{
		struct MiO_Map *m = &map[i];

		if (m->flags & MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS)
		{
			long v = le64toh(m->virtual);
			if (v < firstVirtual)
			{
				firstVirtual = v;
			}
			if (v > lastVirtual)
			{
				lastVirtual = v;
			}
		}
	}

	// fill out alignments
	for (long i = 0; i<maps; i++)
	{
		struct MiO_Map *m = &map[i];

		if (m->flags & MIO_MAP_FLAG_THREAD_LOCAL)
		{
			fprintf(stderr, gettext("%s: TLS maps are not flat loadable\n"),
				self);
			errors++;
		}

		if (!(m->flags & MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS))
		{
			long alignment = le64toh(m->virtual);
			long x         = lastVirtual;

			if (alignment) x += alignment-(x&alignment);

			m->virtual = htole64(x);

			lastVirtual = x+le64toh(m->size);
		}

		if (!(m->flags & MIO_MAP_FLAG_PHYSICAL_IS_ADDRESS))
		{
			m->physical = htole64(le64toh(m->virtual)-firstVirtual);
		}
	}
}
