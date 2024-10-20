#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "defs.h"
#include <mio.h>
#include <mio-x86.h>

// TODO: setup an atomic and always free environment, even on forced exits/hard errors

int  yyparse       (void);
void yylex_destroy (void); // lexer clean up, not portable but who cares

char *filename = "<stdin>"; // input file name

const char *self = "as.x86";

int code = 32;

FILE *fout;
const char *fileout = "a.out"; // a.out as default output file name

struct section *currentSection;
struct section *firstSection;
struct symbol  *lastFile;
struct symbol  *lastSymbol;

struct header header = {
	.uarch        = MIO_UARCH_I8086,
	.archFeatures = 0,

	.system      = MIO_SYSTEM_UNKNOWN,
	.abi         = MIO_ABI_UNKNOWN,
	.sysFeatures = 0
};

int
main (int argc, const char **argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	// open ouput file
	fout = fopen(fileout, "w");
	if (!fout)
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to open file `%s' for writing.\n", self, fileout);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}

	currentSection = (struct section *)NULL;
	firstSection   = (struct section *)NULL;
	lastFile       = (struct symbol  *)NULL;
	lastSymbol     = (struct symbol  *)NULL;
	atexit(freeAll); // free all data structures at end of execution

	// parser input
	yyparse();

	yylex_destroy(); // free lexer

	if (!errors)
	{
		// compile symbol and gap tables
		buildSymbolTable();
		buildGapTable();

		// write file header
		writeHeader();
	}

	// print data structures
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

			currentSymbol = nextSymbol;
		}

		// free gaps, and print them
		struct gap *currentGap = currentSection->firstGap;
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
			currentGap = currentGap->next;
		}

		// sections data and bss sizes
		printf("Data size: %ld\n", ftell(currentSection->stream));
		printf("BSS size:  %ld\n", currentSection->bssz);

		currentSection = nextSection; // next section
	}

	return errors;
}
