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
	char nothing[2] = {0xe1, 0xe1}; // dumby data
	switch (flags&MIO_GAP_TYPE_MASK)
	{
	case MIO_GAP_ABSOLUTE_WORD:
		if (fwrite(nothing, 1, 2, currentSection->stream) != 2)
		{
			goto writeerror;
		}
		// grow sizing
		if (lastFile)
		{
			lastFile->size += 2;
		}
		if (lastSymbol)
		{
			lastSymbol->size += 2;
		}
		printf("Parser: Emit Absolute Word Gap `%s'\n", symbol);
		break;
	case MIO_GAP_ABSOLUTE_BYTE:
		if (fwrite(nothing, 1, 1, currentSection->stream) != 1)
		{
			goto writeerror;
		}
		// grow sizing
		if (lastFile)
		{
			lastFile->size++;
		}
		if (lastSymbol)
		{
			lastSymbol->size++;
		}
		printf("Parser: Emit Absolute Byte Gap `%s'\n", symbol);
		break;
	case MIO_GAP_RELATIVE_WORD:
		if (fwrite(nothing, 1, 2, currentSection->stream) != 2)
		{
			goto writeerror;
		}
		// grow sizing
		if (lastFile)
		{
			lastFile->size += 2;
		}
		if (lastSymbol)
		{
			lastSymbol->size += 2;
		}
		printf("Parser: Emit Relative Word Gap `%s'\n", symbol);
		break;
	case MIO_GAP_RELATIVE_BYTE:
		if (fwrite(nothing, 1, 1, currentSection->stream) != 1)
		{
			goto writeerror;
		}
		// grow sizing
		if (lastFile)
		{
			lastFile->size++;
		}
		if  (lastSymbol)
		{
			lastSymbol->size++;
		}
		printf("Parser: Emit Relative Byte Gap `%s'\n", symbol);
		break;
	default:
		printf("Parser: Emit unknown Gap `%s'\n", symbol);
		break;
	}

	// add gap
	struct gap *gap = currentSection->firstGap; // save tail
	currentSection->firstGap = (struct gap *)malloc(sizeof(struct gap));
	int error;
	if (!currentSection->firstGap)
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

	return;
	// failed to write data
writeerror:
	error = errno;
	fprintf(stderr, "%s: Failed to write to output.\n", self);
	fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
	exit(1);
}
