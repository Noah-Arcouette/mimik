#include <stdio.h>
#include "defs.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <mio.h>

void
newFile (const char *file)
{
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

	nextSymbol->name = strdup(file); // duplicate string
	if (!nextSymbol->name)
	{
		goto memerr;
	}

	// initialize this symbol
	nextSymbol->flags = MIO_SYMLIST_TYPE_FILE;
	nextSymbol->size  = currentSection->size;
	nextSymbol->val   = 0;
	nextSymbol->next  = (struct symbol *)NULL;

	// set size for prior symbol
	(*lastSymbol)->size = currentSection->size - (*lastSymbol)->size;

	printf("Parser: In file `%s'\n", file);
}
