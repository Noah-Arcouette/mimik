#include "lang.h"
#include "colors.h"
#include "unreal.h"
#include <stdnoreturn.h>

noreturn void
halt (void)
{
	puts(HALT_MSG, FG_WHITE);

	while (1)
	{
		__asm (
			"cli\n\t"
			"hlt\n\t"
			:
			:
			:
		);
	}
}
