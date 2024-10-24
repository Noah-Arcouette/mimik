//#include "defs.h"
#include <stdio.h>

int  yyparse       (void);
void yylex_destroy (void);

      int   errors = 0;
const char *self   = "usr.bin/cc";

const char *filename = "<stdin>";

int
main (int argc, char *const *argv)
{
	if (argc > 0)
	{
		self = argv[0]; // get program name
	}

	//yyparse();

	//yylex_destroy(); // free the lexer
	printf("%s: Hello, world!\n", self);

	return errors;
}

