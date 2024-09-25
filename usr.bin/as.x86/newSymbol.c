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

	// find end of symbols
	if (!currentSection)
	{
		fprintf(stderr, "%s:%d: Cannot output symbol without section defined first\n", filename, lineno-1);
		errors++;
		return;
	}

	struct symbol  *lastSymbol    = (struct symbol *)NULL;
	struct symbol **currentSymbol = &(currentSection->firstSymbol);
	while (*currentSymbol)
	{
		lastSymbol    = *currentSymbol;
		currentSymbol = &((*currentSymbol)->next);
	}

	// allocate new symbol
	*currentSymbol = (struct symbol *)malloc(sizeof(struct symbol));
	struct symbol *nextSymbol = *currentSymbol;

	int errnum;
	if (!nextSymbol)
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
	nextSymbol->size  = ftell(currentSection->stream);
	nextSymbol->val   = ftell(currentSection->stream);
	nextSymbol->next  = (struct symbol *)NULL;
	if ((type == MIO_SYMLIST_TYPE_ADDRESS) && (currentSection->flags & MIO_SECTION_FLAG_BSS))
	{
		// push up address to BSS if in the bss section
		nextSymbol->flags = MIO_SYMLIST_TYPE_BSS;
		nextSymbol->val   = currentSection->bssz;
	}

	// set size for prior symbol
	if (lastSymbol)
	{
		lastSymbol->size = ftell(currentSection->stream) - lastSymbol->size;
	}
}
