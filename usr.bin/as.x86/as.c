#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include <mio.h>
#include <mio-x86.h>

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

			if (currentSymbol->flags & MIO_SYMLIST_GLOBAL)
			{
				printf("G ");
			}

			switch (currentSymbol->flags & MIO_SYMLIST_TYPE_MASK)
			{
			case MIO_SYMLIST_TYPE_FILE:
				printf("\tf ");
				break;
			case MIO_SYMLIST_TYPE_BSS:
				printf("\tb ");
				break;
			case MIO_SYMLIST_TYPE_ADDRESS:
				printf("\tp ");
				break;
			default:
				printf("\t? ");
				break;
			}
			printf("%s %zu(%zuB)\n", currentSymbol->name, currentSymbol->val, currentSymbol->size);

			free(currentSymbol->name);
			free(currentSymbol);

			currentSymbol = nextSymbol;
		}

		// free relocations
		struct reloc *currentReloc = currentSection->firstReloc;
		struct reloc *nextReloc;
		while (currentReloc)
		{
			printf("Relocate `%s' at %lx, type: ", currentReloc->name, currentReloc->offset);
			switch (currentReloc->flags&MIO_RELOC_TYPE_MASK)
			{
			case MIO_RELOC_ABSOLUTE_WORD:
				printf("Absolute word.");
				break;
			case MIO_RELOC_ABSOLUTE_BYTE:
				printf("Absolute byte.");
				break;
			case MIO_RELOC_RELATIVE_WORD:
				printf("Relative word.");
				break;
			case MIO_RELOC_RELATIVE_BYTE:
				printf("Relative byte.");
				break;
			}

			if (currentReloc->flags & MIO_RELOC_FLAG_EXECUTE)
			{
				printf(" Executable");
			}
			if (currentReloc->flags & MIO_RELOC_FLAG_READ)
			{
				printf(" Readable");
			}
			if (currentReloc->flags & MIO_RELOC_FLAG_WRITE)
			{
				printf(" Writable");
			}

			putchar('\n');

			nextReloc = currentReloc->next;
			free(currentReloc->name);
			free(currentReloc);
			currentReloc = nextReloc;
		}

		printf("Data size: %ld\n", ftell(currentSection->stream));
		printf("BSS size:  %ld\n", currentSection->bssz);

		// free data
		if (currentSection->stream)
		{
			fclose(currentSection->stream);
			free(currentSection->buffer);
		}
		free(currentSection->name);
		free(currentSection);

		currentSection = nextSection;
	}

	return errors;
}
