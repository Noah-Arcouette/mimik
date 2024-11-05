%{
#include "defs.h"

int errors = 0;

#define YY_NO_LEAKS
%}

%start program
%%

program:
	;

%%

int
yyerror (const char *msg)
{
	fprintf(stderr, "%s\n", msg);

	errors++;
	return 0;
}

