#include "functions.h"

[[noreturn]] void
_start (void)
{
	struct mbr_part *mbr = find_mbr_partition();
	if (!mbr)
	{
		puts("No bootable partition\n\r");
		halt();
	}

	halt();
}
