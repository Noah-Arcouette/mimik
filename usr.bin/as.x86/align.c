#include "defs.h"
#include <stdio.h>

void
align (size_t alignment)
{
	printf("Parser: Align %zu\n", alignment);

	size_t rem = ftell(currentSection->stream) % alignment;

	while (rem--)
	{
		fputc(0xe1, currentSection->stream);
	}
}
