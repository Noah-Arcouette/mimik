#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "defs.h"
#include <mio.h>
#include <mio-x86.h>

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
main (int argc, char * const*argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	opterr = 0;
	int c;
	while (1)
	{
		c = getopt(argc, argv, ":m:o:");
		if (c < 0)
		{
			break; // leave on end of getopt
		}

		switch (c)
		{
		case '?':
			fprintf(stderr, "%s: Unknown option `%c'\n", self, optopt);
			exit(1);
			break;
		case ':':
			fprintf(stderr, "%s: Option `%c' requires a parameter.\n", self, optopt);
			exit(1);
			break;
		case 'm': // micro-architecture
			if (!strcmp(optarg, "i8086"))
			{
				header.uarch = MIO_UARCH_I8086;
				break;
			}
			if (!strcmp(optarg, "i386"))
			{
				header.uarch = MIO_UARCH_I386;
				break;
			}
			fprintf(stderr, "%s: Unknown micro-architecture `%s'.\n", self, optarg);
			exit(1);
			break;
		case 'o': // output file
			fileout = optarg;
			break;
		}
	}
	if (optind < argc && !strcmp(argv[optind], "--"))
	{
		optind++; // skip over `--'
	}
	// check for input file
	if (optind < argc)
	{
		filename = argv[optind];
		yyin     = fopen(filename, "r"); // open parameter file
		if (!yyin)
		{
			int errnum = errno;
			fprintf(stderr, "%s: Failed to open file `%s'\n", self, filename);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
			exit(1);
		}
	}

	currentSection = (struct section *)NULL;
	firstSection   = (struct section *)NULL;
	lastFile       = (struct symbol  *)NULL;
	lastSymbol     = (struct symbol  *)NULL;
	atexit(freeAll); // free all data structures at end of execution

	// parser input
	yyparse();

	// yylex_destroy does weird things to the pointer so put it above
	if (yyin && yyin != stdin)
	{
		fclose(yyin);
	}

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

		// write data
		writeData();
	}

	return errors;
}
