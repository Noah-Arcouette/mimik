#define _BSD_SOURCE
#include <stdio.h>
#include <endian.h>
#include "defs.h"
#include "y.tab.h"

void
emit (size_t val, int type)
{
	switch (type)
	{
	case BYTE:
		printf("Parser: Emit Byte %02x\n", (unsigned char)val);
		fwrite(&val, 1, 1, currentSection->stream);
		break;
	case WORD:
		printf("Parser: Emit Word %04x\n", (unsigned short)val);
		val = htole16((unsigned short)val);
		fwrite(&val, 2, 1, currentSection->stream);
		break;
	case SHORT:
		printf("Parser: Emit Short %d\n", (short)val);
		val = htole16((unsigned short)val);
		fwrite(&val, 2, 1, currentSection->stream);
		break;
	case INT:
		printf("Parser: Emit Int %d\n", (int)val);
		val = htole32((unsigned int)val);
		fwrite(&val, 4, 1, currentSection->stream);
		break;
	case LONG:
		printf("Parser: Emit Long %ld\n", (long)val);
		val = htole64((unsigned long)val);
		fwrite(&val, 8, 1, currentSection->stream);
		break;
	default:
		printf("Parser: Emit unknown %zx\n", val);
		break;
	}
}
