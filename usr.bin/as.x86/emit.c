#include <stdio.h>
#include "defs.h"
#include "y.tab.h"

void
emit (size_t val, int type)
{
	switch (type)
	{
	case BYTE:
		printf("Parser: Emit Byte %02x\n", (unsigned char)val);
		break;
	case WORD:
		printf("Parser: Emit Word %04x\n", (unsigned short)val);
		break;
	case SHORT:
		printf("Parser: Emit Short %d\n", (short)val);
		break;
	case INT:
		printf("Parser: Emit Int %d\n", (int)val);
		break;
	case LONG:
		printf("Parser: Emit Int %ld\n", (long)val);
		break;
	default:
		printf("Parser: Emit unknown %zx\n", val);
		break;
	}
}
