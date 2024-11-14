#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "defs.h"

const char *filename = "<stdin>";
enum token  token;
size_t      errors = 0;
const char *self = "cc";

int
main (int argc, char * const* argv)
{
	yyout = stdout;

	if (argc > 0)
	{
		self = argv[0]; // get program name
	}

	atexit((void(*)(void))yylex_destroy);
	atexit(               freeContexts );

	token = (enum token)yylex();
	root();

	return errors;
}
