#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "defs.h"

struct MiO_Header currentHeader;

void
printMiO (FILE *f)
{
	// read headers
	size_t headerIdx = 0;
	size_t sectionIdx;
	struct MiO_Section section;
struct MiO_Data    data;
	getDataStart(f);
	do
	{
		printf("\nHeader[%zu]:\n", headerIdx); // say what header we're in

		// read the header
		if (fread(&currentHeader, sizeof(struct MiO_Header), 1, f) != 1)
		{
			printError(errno, "Failed to read header.\n");
			return; // leave
		}

		// validate the header
		if (memcmp(currentHeader.magic, MIO_MAGIC, sizeof(currentHeader.magic)))
		{
			printError(0, "Corrupt magic number, got `%.*s'.\n", sizeof(currentHeader.magic), currentHeader.magic);
			return; // leave
		}
		if (currentHeader.version != MIO_CURRENT_VERSION)
		{
			printError(0, "Unsupported MiO version, got %d.\n", currentHeader.version);
			return; // leave
		}

		// print header
		printHeader(currentHeader);

		// print sections
		sectionIdx = 0;
		do {
			printf("\nSection[%zu]:\n", sectionIdx);

			// read in the section
			if (fread(&section, sizeof(struct MiO_Section), 1, f) != 1)
			{
				// failed
				printError(errno, "Failed to read section header.\n");
				return;
			}

			sectionIdx++; // next section
		} while(!(section.flags & MIO_SECTION_FLAG_LAST)); // until last section
		// read data

		headerIdx++; // next header
	} while (!(currentHeader.flags & MIO_HEADER_FLAG_LAST)); // until last header
}
