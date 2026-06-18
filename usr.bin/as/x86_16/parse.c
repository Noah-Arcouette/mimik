#include "../parse.h"
#include "x86_16.h"

int
parse_x86_16 (void)
{
	if (parse_x86_16_jmp()) return 1;

	if (parse_x86_16_singlet("hlt", 0b11110100)) return 1;

	return 0;
}
