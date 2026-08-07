#include <mbr.h>

[[noreturn]] void
load_partition (struct mbr_part *p)
{
	halt();
}
