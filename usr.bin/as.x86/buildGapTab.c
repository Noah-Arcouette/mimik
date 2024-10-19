#include <stdio.h>
#include "defs.h"
#include <mio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void
buildGapTable (void)
{
	enterSection(MIO_GAP_NAME, "");

	struct section *csect = firstSection; // current section
	struct gap     *cgap; // current gap
	struct MiO_Gap  gap; // MiO gap
	size_t fileoff = 0;     // file offset
	// for each section
	while (csect)
	{
		// first gap
		cgap = csect->firstGap;

		// for each gap
		while (cgap)
		{
			strncpy((char *)&gap.name, cgap->name, sizeof(gap.name)); // copy name into buffer

			size_t off = htole64(cgap->offset+fileoff); // convert to little endian
			memcpy(gap.offset, (void *)&off, 8); // copy to structure

			gap.type = cgap->flags; // set type

			// write structure to section
			if (fwrite(&gap, sizeof(struct MiO_Gap), 1, currentSection->stream) != 1) // failed to write
			{
				int errnum = errno;
				fprintf(stderr, "%s: Failed to write to stream.\n", self);
				fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
				exit(1);
			}

			cgap = cgap->next; // next gap
		}

		fileoff += ftell(csect->stream); // add to file offset

		csect = csect->next; // next section
	}
}
