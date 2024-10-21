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

FILE *fout          = (FILE *)NULL;
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

		// open ouput file
		fout = fopen(fileout, "w");
		if (!fout)
		{
			int errnum = errno;
			fprintf(stderr, "%s: Failed to open file `%s' for writing.\n", self, fileout);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
			exit(1);
		}

		// write file header
		writeHeader();

		// write sections
		writeSections();
	}

	// print data structures
	struct section *nextSection;
	currentSection = firstSection;
	while (currentSection)
	{
		nextSection = currentSection->next;

		// sections data and bss sizes
		printf("Data size: %ld\n", ftell(currentSection->stream));
		printf("BSS size:  %ld\n", currentSection->bssz);

		currentSection = nextSection; // next section
	}

	return errors;
}
