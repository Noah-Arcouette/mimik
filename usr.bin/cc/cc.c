#include "defs.h"
#include <stdlib.h>

int
main (void)
{
	atexit(yylex_destroy); // free lex at program exit

	// parse input
	yyparse();

	return errors;
}

