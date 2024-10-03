#include "defs.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void
align (size_t alignment)
{
	if (!currentSection)
	{
		fprintf(stderr, "%s:%d: Alignment without being in a section.\n", filename, lineno-1);
		return;
	}
	printf("Parser: Align %zu\n", alignment);

	// amount needed to align properly
	size_t rem = ftell(currentSection->stream) % alignment;

	// grow sizing
	if (lastFile)
	{
		lastFile->size += rem; 
	}
	if (lastSymbol)
	{
		lastSymbol->size += rem;
	}
	
	while (rem--)
	{
		// 0xe1 is a random number for padding
		if (fputc(0xe1, currentSection->stream) == EOF)
		{
			int error = errno;
			fprintf(stderr, "%s: Cannot output data.\n", self);
			fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
			exit(1);
		}
	}
}
