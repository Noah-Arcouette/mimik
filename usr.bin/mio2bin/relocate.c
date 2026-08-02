#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>

long
relocate (long off, short virtual)
{
	for (long j = 0; j<maps; j++)
	{
		struct MiO_Map *m = &map[j];

		// find the right map
		short mapIsVirtual = 0;
		if (m->flags & MIO_MAP_FLAG_VIRTUAL) mapIsVirtual = 1;

		// must both be virtual
		if (mapIsVirtual != virtual) continue;

		// check if its loaded from this map
		long mapStart = le64toh(m->from);
		long mapEnd   = le64toh(m->amount)+mapStart;

		if (off >= mapStart && off <= mapEnd)
		{
			return off-mapStart+le64toh(m->virtual);
		}
	}
	return -1;
}
