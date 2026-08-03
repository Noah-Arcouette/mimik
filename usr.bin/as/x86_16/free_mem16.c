#include "x86_16.h"
#include <stdlib.h>

void
free_x86_16_mem16 (struct mem16 *mem16)
{
	mem16->modrm = 0;
	mem16->displacement[0] = 0;
	mem16->displacement[1] = 0;
	free(mem16->symbol);
	mem16->symbol = NULL;
}
