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
struct symbol  *lastFile;
struct symbol  *lastSymbol;

int
main (int argc, const char **argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	currentSection = (struct section *)NULL;
	firstSection   = (struct section *)NULL;
	lastFile       = (struct symbol  *)NULL;
	lastSymbol     = (struct symbol  *)NULL;

	// parser input
	yyparse();

	// free data structures, and print them
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

			// whether global or not
			if (currentSymbol->flags & MIO_SYMLIST_GLOBAL)
			{
				printf("G ");
			}

			// symbol type
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
			// name, place, and size
			printf("%s %zu(%zuB)\n", currentSymbol->name, currentSymbol->val, currentSymbol->size);

			// free them
			free(currentSymbol->name);
			free(currentSymbol);

			currentSymbol = nextSymbol;
		}

		// free relocations, and print them
		struct reloc *currentReloc = currentSection->firstReloc;
		struct reloc *nextReloc;
		while (currentReloc)
		{
			// name and place
			printf("Relocate `%s' at %zu, type: ", currentReloc->name, currentReloc->offset);
			// type
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

			// flags
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

			// free them and move onto the next
			nextReloc = currentReloc->next;
			free(currentReloc->name);
			free(currentReloc);
			currentReloc = nextReloc;
		}

		// sections data and bss sizes
		printf("Data size: %ld\n", ftell(currentSection->stream));
		printf("BSS size:  %ld\n", currentSection->bssz);

		// free data
		if (currentSection->stream)
		{
			fclose(currentSection->stream); // close output stream
			free(currentSection->buffer);
		}
		free(currentSection->name);
		free(currentSection);

		currentSection = nextSection; // next section
	}

	return errors;
}
