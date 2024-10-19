#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include <mio.h>
#include <mio-x86.h>

// TODO: setup an atomic and always free environment, even on forced exits/hard errors

int  yyparse       (void);
void yylex_destroy (void); // lexer clean up, not portable but who cares

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

	if (!errors)
	{
		// compile symbol and gap tables
		buildSymbolTable();
		buildGapTable();
	}

	yylex_destroy(); // clean up lexer

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

		// free gaps, and print them
		struct gap *currentGap = currentSection->firstGap;
		struct gap *nextGap;
		while (currentGap)
		{
			// name and place
			printf("Fill gap `%s' at %zu, type: ", currentGap->name, currentGap->offset);
			// type
			switch (currentGap->flags&MIO_GAP_TYPE_MASK)
			{
			case MIO_GAP_ABSOLUTE_WORD:
				printf("Absolute word.");
				break;
			case MIO_GAP_ABSOLUTE_BYTE:
				printf("Absolute byte.");
				break;
			case MIO_GAP_RELATIVE_WORD:
				printf("Relative word.");
				break;
			case MIO_GAP_RELATIVE_BYTE:
				printf("Relative byte.");
				break;
			}

			// flags
			if (currentGap->flags & MIO_GAP_FLAG_EXECUTE)
			{
				printf(" Executable");
			}
			if (currentGap->flags & MIO_GAP_FLAG_READ)
			{
				printf(" Readable");
			}
			if (currentGap->flags & MIO_GAP_FLAG_WRITE)
			{
				printf(" Writable");
			}

			putchar('\n');

			// free them and move onto the next
			nextGap = currentGap->next;
			free(currentGap->name);
			free(currentGap);
			currentGap = nextGap;
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
