#include "functions.h"

[[noreturn]] void
halt (void)
{
	puts("Halting...\n\r");

	while (1)
	{
		__asm__ (
			"cli\n"
			"hlt\n"
		);
	}
}
