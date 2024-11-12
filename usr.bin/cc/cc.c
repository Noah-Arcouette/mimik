#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

	  FILE *fout;
const char *filename;
const char *self = "cc";

int
main (int argc, const char **argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	atexit((void(*)(void))yylex_destroy);   // free lex at program exit
	atexit(               freeAllContexts); // free contexts
	atexit(               freeInfo);        // free information stack

	fout     = stdout; // output for standard out
	filename = "<stdin>";

	// parse input
	yyparse();

	return errors;
}

