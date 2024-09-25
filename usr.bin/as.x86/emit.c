#define _DEFAULT_SOURCE // glibc compatibility
#include <stdio.h>
#include <endian.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <mio.h>
#include "defs.h"
#include "y.tab.h"

void
emit (size_t val, int type)
{
	switch (type)
	{
	case BYTE:
		printf("Parser: Emit Byte %02x\n", (unsigned char)val);
		if (currentSection->flags & MIO_SECTION_FLAG_BSS)
		{
			currentSection->bssz++;
			return;
		}
		if (fwrite(&val, 1, 1, currentSection->stream) != 1)
		{
			goto error;
		}
		break;
	case WORD:
		printf("Parser: Emit Word %04x\n", (unsigned short)val);
		if (currentSection->flags & MIO_SECTION_FLAG_BSS)
		{
			currentSection->bssz += 2;
			return;
		}
		val = htole16((unsigned short)val);
		if (fwrite(&val, 1, 2, currentSection->stream) != 2)
		{
			goto error;
		}
		break;
	case SHORT:
		printf("Parser: Emit Short %d\n", (short)val);
		if (currentSection->flags & MIO_SECTION_FLAG_BSS)
		{
			currentSection->bssz += 2;
			return;
		}
		val = htole16((unsigned short)val);
		if (fwrite(&val, 1, 2, currentSection->stream) != 2)
		{
			goto error;
		}
		break;
	case INT:
		printf("Parser: Emit Int %d\n", (int)val);
		if (currentSection->flags & MIO_SECTION_FLAG_BSS)
		{
			currentSection->bssz += 4;
			return;
		}
		val = htole32((unsigned int)val);
		if (fwrite(&val, 1, 4, currentSection->stream) != 4)
		{
			goto error;
		}
		break;
	case LONG:
		printf("Parser: Emit Long %ld\n", (long)val);
		if (currentSection->flags & MIO_SECTION_FLAG_BSS)
		{
			currentSection->bssz += 8;
			break;
		}
		val = htole64((unsigned long)val);
		if (fwrite(&val, 1, 8, currentSection->stream) != 8)
		{
			goto error;
		}
		break;
	default:
		printf("Parser: Emit unknown %zx\n", val);
		break;
	}

	return;
	int errnum;
error:
	errnum = errno;
	fprintf(stderr, "%s: Failed to output data.\n", self);
	fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
	exit(1);
}
