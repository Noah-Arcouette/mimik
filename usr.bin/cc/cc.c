#include <stdio.h>
#include <ctype.h>
#include "defs.h"

const char *filename = "<stdin>";
enum token  token;
size_t      errors = 0;
const char *self = "cc";

int
main (int argc, char * const* argv)
{
	if (argc > 0)
	{
		self = argv[0]; // get program name
	}

	token = (enum token)yylex();
	extern_();
	yylex_destroy();

	return errors;
}
