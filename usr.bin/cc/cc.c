#include <stdio.h>
#include <ctype.h>
#include "defs.h"

const char *filename = "<stdin>";
enum token  token;

int
main (void)
{
	while ((token = (enum token)yylex()))
	{
		switch (token)
		{
		// = Key words =
		case EXTERN:
			fprintf(stderr, "EXTERN\n");
			break;
		// = Types =
		case INT:
			fprintf(stderr, "INT\n");
			break;
		// = Symbol =
		case SYMBOL:
			fprintf(stderr, "SYMBOL `%s'\n", yytext);
			break;
		// = characters =
		case SEMICOLON:
			fprintf(stderr, "SEMICOLON\n");
			break;
		default:
			fprintf(stderr, "(UNKNOWN)");
			break;
		}
	}
	yylex_destroy();

	return 0;
}
