#include <stdio.h>
#include <ctype.h>
#include "defs.h"

const char *filename = "<stdin>";

int
main (void)
{
	int l;
	while ((l = yylex()))
	{
		switch (l)
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
		default:
			fprintf(stderr, "%c\n", l);
			break;
		}
	}
	yylex_destroy();

	return 0;
}
