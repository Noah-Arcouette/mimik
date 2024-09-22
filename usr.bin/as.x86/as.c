#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include <mio.h>

int yyparse (void);

char *filename = "<stdin>"; // input file name

const char *self = "as.x86";

int code = 32;

struct section *currentSection;
struct section *firstSection;

int
main (int argc, const char **argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	currentSection = (struct section *)NULL;
	firstSection   = (struct section *)NULL;

	// parser input
	yyparse();

	// free data structures
	struct section *nextSection;
	currentSection = firstSection;
	while (currentSection)
	{
		printf("%s\n", currentSection->name);

		nextSection = currentSection->next;

		// free symbols
		struct symbol *nextSymbol;
		struct symbol *currentSymbol = currentSection->firstSymbol;
		while (currentSymbol)
		{
			nextSymbol = currentSymbol->next;

			switch (currentSymbol->flags)
			{
			case MIO_SYMLIST_TYPE_FILE:
				printf("\t\"%s\" %zu\n", currentSymbol->name, currentSymbol->size);
				break;
			case MIO_SYMLIST_TYPE_BSS:
				printf("\tb %s, %zu(%zuB)\n", currentSymbol->name, currentSymbol->size, currentSymbol->val);
				break;
			case MIO_SYMLIST_TYPE_ADDRESS:
				printf("\tp %s, %zu(%zuB)\n", currentSymbol->name, currentSymbol->size, currentSymbol->val);
				break;
			default:
				printf("\t?%s\n %zu(%zuB)\n", currentSymbol->name, currentSymbol->size, currentSymbol->val);
				break;
			}

			free(currentSymbol->name);
			free(currentSymbol);

			currentSymbol = nextSymbol;
		}

		// free data
		free(currentSection->name);
		free(currentSection->byte);
		free(currentSection);

		currentSection = nextSection;
	}

	return errors;
}
