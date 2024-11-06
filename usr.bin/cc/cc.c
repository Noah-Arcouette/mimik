#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

      FILE *fout;
const char *filename;

int
main (void)
{
	atexit((void(*)(void))yylex_destroy); // free lex at program exit

	fout     = stdout; // output for standard out
	filename = "<stdin>";

	// parse input
	yyparse();

	return errors;
}

