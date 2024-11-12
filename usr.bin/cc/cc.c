#include <stdio.h>
#include <ctype.h>
#include "defs.h"

const char *filename = "<stdin>";
enum token  token;
size_t      errors = 0;

int
main (void)
{
	token = (enum token)yylex();
	extern_();
	yylex_destroy();

	return errors;
}
