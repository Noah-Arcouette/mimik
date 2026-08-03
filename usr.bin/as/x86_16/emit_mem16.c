#include "../emit.h"
#include "x86_16.h"
#include <stdlib.h>

void
emit_x86_16_mem16 (const struct mem16 *mem16)
{
	// modrm
	emit(&mem16->modrm, 1);

	size_t dispsz = 0;
	// displacement
	switch (mem16->modrm & 0xc0)
	{
	case 0x00: // no disp
		break;
	case 0x40: // 8bit disp
		dispsz = 1;
		break;
	case 0x80: // 16bit disp
		dispsz = 2;
		break;
	case 0xc0: // no disp
		break;
	}

	// [literal]
	if ((mem16->modrm & 0xc7) == 0x06)
	{
		// 16bit disp
		dispsz = 2;
	}

	if (!dispsz) return;

	// emit disp
	if (mem16->symbol)
	{
		emitGap(mem16->symbol, mem16->gapType);
	}
	else
	{
		emit(mem16->displacement, dispsz);
	}
}
