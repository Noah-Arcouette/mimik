#include <mio.h>
#include <mio-x86.h>
#include <stdio.h>
#include "defs.h"

void
emitRelocation(int type, const char *symbol)
{
	switch (type&MIO_RELOC_TYPE_MASK)
	{
	case MIO_RELOC_ABSOLUTE_WORD:
		printf("Parser: Emit Absolute Word Relocation `%s'\n", symbol);
		break;
	case MIO_RELOC_ABSOLUTE_BYTE:
		printf("Parser: Emit Absolute Byte Relocation `%s'\n", symbol);
		break;
	case MIO_RELOC_RELATIVE_WORD:
		printf("Parser: Emit Relative Word Relocation `%s'\n", symbol);
		break;
	case MIO_RELOC_RELATIVE_BYTE:
		printf("Parser: Emit Relative Byte Relocation `%s'\n", symbol);
		break;
	default:
		printf("Parser: Emit unknown relocation `%s'\n", symbol);
		break;
	}
}
