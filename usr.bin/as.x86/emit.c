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
	if (!currentSection)
	{
		fprintf(stderr, "%s:%d: Cannot emit data outside of a section.\n", filename, lineno-1);
		errors++;
		return;
	}

	int size = 0;
	switch (type)
	{
	case BYTE:
		printf("Parser: Emit Byte %02x\n", (unsigned char)val);
		size = 1; // set and format value
		val  = val&0xff;
		break;
	case WORD:
		printf("Parser: Emit Word %04x\n", (unsigned short)val);
		size = 2; // set and format value
		val  = htole16(val&0xffff);
		break;
	case DWORD:
		printf("Parser: Emit Double Word %08x\n", (unsigned int)val);
		size = 4;
		val = htole32(val&0xffffffff);
		break;
	case QWORD:
		printf("Parser: Emit Quad Word %016lx\n", (long)val);
		size = 8;
		val = htole64(val&0xffffffffffffffff);
		break;
	default:
		printf("Parser: Emit unknown %zx\n", val);
		exit(-1);
		break;
	}
	
	// grow sizing
	if (lastFile)
	{
		lastFile->size += size;
	}
	if (lastSymbol)
	{
		lastSymbol->size += size;
	}
	// if in bss
	if (currentSection->flags & MIO_SECTION_FLAG_BSS)
	{
		// grow bss
		currentSection->bssz += size;
		return;
	}

	// in data, write to output stream
	if (fwrite(&val, size, 1, currentSection->stream) == 1)
	{
		return;
	}
	
	// output failed case
	int errnum = errno;
	fprintf(stderr, "%s: Failed to output data.\n", self);
	fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
	exit(1);
}
