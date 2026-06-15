#include "../parse.h"
#include "x86_16.h"

int
parse_x86_16 (void)
{
	if (parse_x86_16_jmp()) return 1;

	return 0;
}
