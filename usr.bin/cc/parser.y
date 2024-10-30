%{

#include "defs.h"
#include <stdio.h>

#define YY_NO_LEAKS // tell yacc to free its data
%}

%start program
%%

program:
	value ';' program
	|
	;

// immediate value
value:
	;

%%

void
yyerror (const char *msg)
{
	fprintf(stderr, "%s:%d: %s.\n", filename, lineno, msg);
}
