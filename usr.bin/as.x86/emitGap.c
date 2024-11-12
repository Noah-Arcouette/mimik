#include <mio.h>
#include <mio-x86.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

void
emitGap(int flags, const char *symbol)
{
	// check if we're in a section
	if (!currentSection)
	{
		fprintf(stderr, "%s:%d: Cannot emit gap outside of section.\n", filename, lineno-1);
		errors++;
		return;
	}

	// check to see if in BSS section, no gaps allowed in BSS
	if (currentSection->flags & MIO_SECTION_FLAG_BSS)
	{
		fprintf(stderr, "%s:%d: Not allowed to reserve a gap inside a BSS section.\n", filename, lineno-1);
		errors++;
		return;
	}

	size_t currentPosition = ftell(currentSection->stream);

	// output dumby data
	char nothing[8] = {0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1}; // dumby data
	int  size       = 0;
	switch (flags&MIO_GAP_TYPE_MASK)
	{
	case MIO_GAP_ABSOLUTE_QWORD:
		printf("Parser: Emit Absolute Quad Word Gap `%s'\n", symbol);
		size = 8;
		break;
	case MIO_GAP_ABSOLUTE_DWORD:
		printf("Parser: Emit Absolute Double Word Gap `%s'\n", symbol);
		size = 4;
		break;
	case MIO_GAP_ABSOLUTE_WORD:
		printf("Parser: Emit Absolute Word Gap `%s'\n", symbol);
		size = 2;
		break;
	case MIO_GAP_ABSOLUTE_BYTE:
		printf("Parser: Emit Absolute Byte Gap `%s'\n", symbol);
		size = 1;
		break;
	case MIO_GAP_RELATIVE_QWORD:
		printf("Parser: Emit Relative Quad Word Gap `%s'\n", symbol);
		size = 8;
		break;
	case MIO_GAP_RELATIVE_DWORD:
		printf("Parser: Emit Relative Double Word Gap `%s'\n", symbol);
		size = 4;
		break;
	case MIO_GAP_RELATIVE_WORD:
		printf("Parser: Emit Relative Word Gap `%s'\n", symbol);
		size = 2;
		break;
	case MIO_GAP_RELATIVE_BYTE:
		printf("Parser: Emit Relative Byte Gap `%s'\n", symbol);
		size = 1;
		break;
	default:
		printf("Parser: Emit unknown Gap `%s'\n", symbol);
		exit(-1);
		break;
	}

	int error;
	if (fwrite(nothing, size, 1, currentSection->stream) != 1)
	{
		error = errno;
		fprintf(stderr, "%s: Failed to write to output.\n", self);
		fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
		exit(1);
	}
	// grow sizing
	if (lastFile)
	{
		lastFile->size += size;
	}
	if  (lastSymbol)
	{
		lastSymbol->size += size;
	}

	// add gap
	struct gap *gap = currentSection->firstGap; // save tail
	currentSection->firstGap = (struct gap *)malloc(sizeof(struct gap));
	if (!currentSection->firstGap) // memory allocation error
	{
		currentSection->firstGap = gap; // reset tail
	memerror:
		error = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
		exit(1);
	}
	// attach tail
	currentSection->firstGap->next = gap;
	gap = currentSection->firstGap; // dereference
	gap->name = strdup(symbol);
	if (!gap->name)
	{
		goto memerror;
	}
	gap->flags  = flags;
	gap->offset = currentPosition;
}
