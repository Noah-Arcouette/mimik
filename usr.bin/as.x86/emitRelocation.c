#include <mio.h>
#include <mio-x86.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

void
emitRelocation(int flags, const char *symbol)
{
	if (!currentSection)
	{
		fprintf(stderr, "%s:%d: Cannot emit relocation outside of section.\n", filename, lineno-1);
		return;
	}
	// check to see if in BSS section, no relocations in BSS

	size_t currentPosition = ftell(currentSection->stream);

	// output dumby data
	char nothing[2] = {0xe1, 0xe1}; // dumby data
	switch (flags&MIO_RELOC_TYPE_MASK)
	{
	case MIO_RELOC_ABSOLUTE_WORD:
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
		printf("Parser: Emit Absolute Word Relocation `%s'\n", symbol);
		break;
	case MIO_RELOC_ABSOLUTE_BYTE:
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
		printf("Parser: Emit Absolute Byte Relocation `%s'\n", symbol);
		break;
	case MIO_RELOC_RELATIVE_WORD:
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
		printf("Parser: Emit Relative Word Relocation `%s'\n", symbol);
		break;
	case MIO_RELOC_RELATIVE_BYTE:
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
		printf("Parser: Emit Relative Byte Relocation `%s'\n", symbol);
		break;
	default:
		printf("Parser: Emit unknown relocation `%s'\n", symbol);
		break;
	}

	// add relocation
	struct reloc *reloc = currentSection->firstReloc; // save tail
	currentSection->firstReloc = (struct reloc *)malloc(sizeof(struct reloc));
	if (!currentSection->firstReloc)
	{
		int error;
	memerror:
		error = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
		exit(1);
	}
	// attach tail
	currentSection->firstReloc->next = reloc;
	reloc = currentSection->firstReloc; // dereference
	reloc->name = strdup(symbol);
	if (!reloc->name)
	{
		goto memerror;
	}
	reloc->flags  = flags;
	reloc->offset = currentPosition;

	return;
	int error;
	// failed to write data
writeerror:
	error = errno;
	fprintf(stderr, "%s: Failed to write to output.\n", self);
	fprintf(stderr, "Error %d: %s.\n", error, strerror(error));
	exit(1);
}
