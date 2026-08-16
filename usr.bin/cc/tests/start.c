#include "functions.h"

[[noreturn]] void
_start (void)
{
	struct mbr_part *p = find_mbr_partition();
	if (!p)
	{
		puts("Failed to find VBR\n\r");
	}
	halt();
}
