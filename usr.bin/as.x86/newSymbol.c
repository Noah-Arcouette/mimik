#include <stdio.h>
#include "defs.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <mio.h>

void
newSymbol (const char *symbol, int type)
{
	printf("Parser: New symbol, `%s'\n", symbol);

	// are we in a section already
	if (!currentSection)
	{
		fprintf(stderr, "%s:%d: Cannot output symbol without section defined first\n", filename, lineno-1);
		errors++;
		return;
	}

	// find end of symbols
	struct symbol **currentSymbol = &(currentSection->firstSymbol);
	while (*currentSymbol)
	{
		currentSymbol = &((*currentSymbol)->next);
	}

	// allocate new symbol
	*currentSymbol = (struct symbol *)malloc(sizeof(struct symbol));
	struct symbol *nextSymbol = *currentSymbol;

	int errnum;
	if (!nextSymbol) // failed
	{
	memerr:
		errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Errno %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}

	nextSymbol->name = strdup(symbol); // duplicate string
	if (!nextSymbol->name)
	{
		goto memerr;
	}

	// initialize this symbol
	nextSymbol->flags = type;
	nextSymbol->size  = 0;
	nextSymbol->val   = ftell(currentSection->stream);
	nextSymbol->next  = (struct symbol *)NULL;
	if ((type == MIO_SYMLIST_TYPE_ADDRESS) && (currentSection->flags & MIO_SECTION_FLAG_BSS))
	{
		// push up address to BSS if in the bss section
		nextSymbol->flags = MIO_SYMLIST_TYPE_BSS;
		nextSymbol->val   = currentSection->bssz;
	}

	// save lasts
	if (type == MIO_SYMLIST_TYPE_FILE)
	{
		lastFile = nextSymbol;
		return;
	}
	lastSymbol = nextSymbol;
}
