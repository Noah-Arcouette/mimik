#include "defs.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void
align (size_t alignment)
{
	printf("Parser: Align %zu\n", alignment);

	size_t rem = ftell(currentSection->stream) % alignment;

	while (rem--)
	{
		if (fputc(0xe1, currentSection->stream) == EOF)
		{
			int error = errno;
			fprintf(stderr, "%s: Cannot output data.\n", self);
			fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
			exit(1);
		}
	}
}
