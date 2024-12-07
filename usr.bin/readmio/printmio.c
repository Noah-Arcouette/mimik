#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "defs.h"

void
printMiO (FILE *f)
{
	// read headers
	size_t headerIdx = 0;
	struct MiO_Header header;
	do
	{
		printf("\nHeader[%zu]:\n", headerIdx); // say what header we're in

		// read the header
		if (fread(&header, sizeof(struct MiO_Header), 1, f) != 1)
		{
			printError(errno, "Failed to read header.\n", headerIdx);
			break; // leave
		}

		// validate the header
		if (memcmp(header.magic, MIO_MAGIC, sizeof(header.magic)))
		{
			printError(0, "Corrupt magic number, got `%.*s'.\n", headerIdx, sizeof(header.magic), header.magic);
			break; // leave
		}
		if (header.version != MIO_CURRENT_VERSION)
		{
			printError(0, "Unsupported MiO version, got %d.\n", headerIdx, header.version);
		}

		// print header
		// print sections
		//   until last section

		headerIdx++; // next header
	} while (!(header.flags & MIO_HEADER_FLAG_LAST)); // until last header
}
