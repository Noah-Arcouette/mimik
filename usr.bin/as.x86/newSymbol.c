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

	struct symbol **lastSymbol = &(currentSection->firstSymbol);
	while (*lastSymbol)
	{
		lastSymbol = &((*lastSymbol)->next);
	}

	// allocate new symbol
	*lastSymbol = (struct symbol *)malloc(sizeof(struct symbol));
	struct symbol *nextSymbol = *lastSymbol;

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
	if ((type & MIO_SYMLIST_TYPE_ADDRESS) && (currentSection->flags & MIO_SECTION_FLAG_BSS))
	{
		// push up address to BSS if in the bss section
		nextSymbol->flags = MIO_SYMLIST_TYPE_BSS;
	}
	nextSymbol->size  = currentSection->size;
	nextSymbol->val   = currentSection->size;
	nextSymbol->next  = (struct symbol *)NULL;

	// set size for prior symbol
	(*lastSymbol)->size = currentSection->size - (*lastSymbol)->size;
}
