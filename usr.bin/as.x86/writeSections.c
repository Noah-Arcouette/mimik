#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mio.h>
#include "defs.h"

void
writeSections (void)
{
	size_t dataOff = 0;
	size_t bssOff  = 0;
	struct section  *csect = firstSection; // current section
	struct section **last  = &firstSection;

	struct section  *next;
	struct section **lastNext = &firstSection;;
	struct MiO_Section out;
	while (csect)
	{
		next     =  csect->next;
		lastNext = &csect->next; // save last next

		// write name
		strncpy((char *)out.name, csect->name, sizeof(out.name));

		// free section name
		free(csect->name);
		csect->name = (char *)NULL;

		out.flags = csect->flags; // set flags

		// write offset into data/bss portion, and size
		size_t off;
		size_t size;
		// select and format output offset
		if (csect->flags & MIO_SECTION_FLAG_BSS)
		{
			off  = htole64(bssOff     );
			size = htole64(csect->bssz);
			bssOff += size;

			// free unneeded bss section
			*last = next;
			fclose(csect->stream);
			free(csect->buffer);
			free(csect);
		}
		else
		{
			off  = htole64(dataOff             );
			size = htole64(ftell(csect->stream));
			dataOff += size;

			// skip over last BSS sections
			last = lastNext;
		}
		memcpy(out.offset, &off,  sizeof(out.offset)); // copy over offset
		memcpy(out.size,   &size, sizeof(out.size  )); // copy over size

		if (!next) // check for last section
		{
			out.flags |= MIO_SECTION_FLAG_LAST;
		}

		csect = next; // next section

		if (!fwrite(&out, sizeof(out), 1, fout))
		{
			int errnum = errno;
			fprintf(stderr, "%s: Failed to write to file `%s'\n", self, fileout);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
			exit(1);
		}
	}
}
