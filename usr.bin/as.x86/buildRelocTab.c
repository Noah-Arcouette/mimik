#include <stdio.h>
#include "defs.h"
#include <mio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void
buildRelocTable (void)
{
	enterSection(MIO_RELOC_NAME, "");

	struct section *csect = firstSection; // current section
	struct reloc   *creloc; // current relocation
	struct MiO_Reloc reloc; // MiO relocation
	size_t fileoff = 0;     // file offset
	// for each section
	while (csect)
	{
		// first relocation
		creloc = csect->firstReloc;

		// for each relocation
		while (creloc)
		{
			strncpy((char *)&reloc.name, creloc->name, sizeof(reloc.name)); // copy name into buffer

			size_t off = htole64(creloc->offset+fileoff); // convert to little endian
			memcpy(reloc.offset, (void *)&off, 8); // copy to structure

			reloc.type = creloc->flags; // set type

			// write structure to section
			if (fwrite(&reloc, sizeof(struct MiO_Reloc), 1, currentSection->stream) != 1) // failed to write
			{
				int errnum = errno;
				fprintf(stderr, "%s: Failed to write to stream.\n", self);
				fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
				exit(1);
			}

			creloc = creloc->next; // next relocation
		}

		fileoff += ftell(csect->stream); // add to file offset

		csect = csect->next; // next section
	}
}

