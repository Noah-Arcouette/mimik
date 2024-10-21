#include <stdio.h>
#include <stdlib.h>
#include <mio.h>
#include <string.h>
#include <errno.h>
#include "defs.h"

void
writeData (void)
{
	size_t headOffset = ftell(fout);
	struct MiO_Data head;
	memset(&head, 0xe1, sizeof(head)); // buffer out the header till the total size is computed

	int errnum;
	if (!fwrite(&head, sizeof(head), 1, fout))
	{
	error:
		errnum = errno;
		fprintf(stderr, "%s: Failed to write to output file.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}

	size_t totalSize = 0;
	struct section *nextSection;
	struct section *csect = firstSection;
	size_t off = 0;
	while (csect)
	{
		nextSection = csect->next;

		fclose(csect->stream); // close and flush stream
		csect->stream = (FILE *)NULL;

		// write to output
		if (fwrite(csect->buffer+off, 1, csect->size, fout) != csect->size)
		{
			goto error;
		}
		free(csect->buffer);
		csect->buffer = (char *)NULL;

		// add to total size
		totalSize += csect->size;

		free(csect); // free current section
		firstSection = nextSection;
		csect        = nextSection; // next section
	}

	// rewrite header
	fseek(fout, headOffset, SEEK_SET);
	head.format = MIO_DATA_FORMAT_RAW; // data is stored as raw bytes
	// format size data
	totalSize = htole64(totalSize);
	memcpy(head.size, &totalSize, sizeof(head.size));

	// rewrite to file
	if (!fwrite(&head, sizeof(head), 1, fout))
	{
		goto error;
	}
}
