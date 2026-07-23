#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>

void
printMaps (FILE *fp, unsigned long long size)
{
	long off = ftell(fp);

	// get the amount of maps in the section
	long maps = size/sizeof(struct MiO_Map);

	printf("\n");
	if (size % sizeof(struct MiO_Map))
	{
		printf(gettext("\tError, size of section is not \
a multiple of the map data size\n"));
		errors++;
	}

	// print each map out
	while (maps--)
	{
		struct MiO_Map map;
		if (fread(&map, sizeof(map), 1, fp) != 1)
		{
			int error = errno;
			printf(gettext("\tFailed to read from file, %s\n"),
				strerror(error));
			errors++;
			break;
		}

		// print the map data
		printf(gettext("\n\tFlags: %02x ("), map.flags);
		if (map.flags & MIO_MAP_FLAG_READABLE)
		{
			printf(gettext(" Readable"));
		}
		if (map.flags & MIO_MAP_FLAG_WRITABLE)
		{
			printf(gettext(" Writable"));
		}
		if (map.flags & MIO_MAP_FLAG_EXECUTABLE)
		{
			printf(gettext(" Executable"));
		}
		if (map.flags & MIO_MAP_FLAG_THREAD_LOCAL)
		{
			printf(gettext(" Thread-Local"));
		}
		if (map.flags & MIO_MAP_FLAG_VIRTUAL)
		{
			printf(gettext(" Virtual"));
		}
		else
		{
			printf(gettext(" Virtual-Alignment"));
		}
		if (map.flags & MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS)
		{
			printf(gettext(" Virtual-Address"));
		}
		else
		{
			printf(gettext(" Virtual-Alignment"));
		}
		if (map.flags & MIO_MAP_FLAG_PHYSICAL_IS_ADDRESS)
		{
			printf(gettext(" Physical-Address"));
		}
		else
		{
			printf(gettext(" Physical-Alignment"));
		}

		printf(gettext(" )\n\tVirtual  : "));
		if (map.flags & MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS)
		{
			printf(gettext("Address %016llx\n"),
				(unsigned long long)le64toh(map.virtual));
		}
		else
		{
			printf(gettext("Align to %016llx\n"),
				(unsigned long long)le64toh(map.virtual));
		}
		printf(gettext(" %016llx\n\tPhysical : "),
			(unsigned long long)le64toh(map.virtual));
		if (map.flags & MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS)
		{
			printf(gettext("Address"));
		}
		else
		{
			printf(gettext("Align to"));
		}
		printf(gettext(" %016llx\n\tSize     : %llu\
\n\tAmount   : %llu\
\n\tFrom     : %llu\n"),
			(unsigned long long)le64toh(map.physical),
			(unsigned long long)le64toh(map.size),
			(unsigned long long)le64toh(map.amount),
			(unsigned long long)le64toh(map.from));
	}

	// get to the end
	fseek(fp, off+size, SEEK_SET);
}
