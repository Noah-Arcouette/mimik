%{
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t temps = 0;

int errors = 0;

#define YY_NO_LEAKS
%}

// immediate values
%token VALUE

%start program
%%

program:
	program value ';'
	|
	;

// a value
value:
	VALUE  { memcpy(&$$, &$1, sizeof(struct value)); }
	;

%%

int
yyerror (const char *msg)
{
	fprintf(stderr, "%s\n", msg);

	errors++;
	return 0;
}

