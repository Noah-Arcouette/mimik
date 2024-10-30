%{

#include "defs.h"
#include <stdio.h>
#include <string.h>

#define YY_NO_LEAKS // tell yacc to free its data
%}

%token VALUE // immediate value

%start program
%%

program:
	value ';' program { addNode(&root, &$1); }
	| // empty
	;

// immediate value
value:
	VALUE { memcpy(&$$, &$1, sizeof(struct node)); }
	;

%%

void
yyerror (const char *msg)
{
	fprintf(stderr, "%s:%d: %s.\n", filename, lineno, msg);
}
