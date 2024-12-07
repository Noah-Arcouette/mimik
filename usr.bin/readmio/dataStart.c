#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <mio.h>
#include "defs.h"

size_t dataStart;

void
getDataStart (FILE *fp)
{
	// read all headers
	struct MiO_Header  h;
	struct MiO_Section s;
	struct MiO_Data    d;
	do
	{
		if (fread(&h, sizeof(h), 1, fp) != 1)
		{
		err:
			printError(errno, "Failed to read from file while trying to get data position.\n");
			dataStart = 0;
			return;
		}

		// read all sections
		do
		{
			if (fread(&s, sizeof(s), 1, fp) != 1)
			{
				goto err;
			}
		} while (!(s.flags & MIO_SECTION_FLAG_LAST)); // until last section
	} while (!(h.flags & MIO_HEADER_FLAG_LAST)); // until last header
	// read data header
	if (fread(&d, sizeof(d), 1, fp) != 1)
	{
		goto err;
	}

	dataStart = ftell(fp); // now at the start of the data

	fseek(fp, 0L, SEEK_SET); // back to the start of the file
}
