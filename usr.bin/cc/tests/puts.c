#include "functions.h"

void
puts (const char *s)
{
	while (*s)
	{
		__asm__(
			"int 0x10\n"
			: // no outputs
			: "ah"(0x0e), "al"(*s), "bh"(0)
			: "cc", "ax" // clobbers
		);

		s++;
	}
}
