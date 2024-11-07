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

// associatiity
%left '+' '-'
%left '*' '/' '%'

%left '>' '<' GTE LTE EQU NEQ

%start program
%%

program:
	program value ';'
	|
	;

// a value
value:
	  VALUE  { memcpy(&$$, &$1, sizeof(struct value)); }
	| expr   { memcpy(&$$, &$1, sizeof(struct value)); }
	;
expr:
	'(' value ')' {
		memcpy(&$$, &$2, sizeof(struct value));
	}
	// comparisons
	| value '>' value {
		if (expr(&$$, $1, $3, "gt"))
		{
			YYERROR;
		}
	}
	| value '<' value {
		if (expr(&$$, $1, $3, "lt"))
		{
			YYERROR;
		}
	}
	| value GTE value {
		if (expr(&$$, $1, $3, "gte"))
		{
			YYERROR;
		}
	}
	| value LTE value {
		if (expr(&$$, $1, $3, "lte"))
		{
			YYERROR;
		}
	}
	| value EQU value {
		if (expr(&$$, $1, $3, "equ"))
		{
			YYERROR;
		}
	}
	| value NEQ value {
		if (expr(&$$, $1, $3, "neq"))
		{
			YYERROR;
		}
	}
	// basic math operations
	| value '+' value {
		if (expr(&$$, $1, $3, "add"))
		{
			YYERROR;
		}
	}
	| value '-' value {
		if (expr(&$$, $1, $3, "sub"))
		{
			YYERROR;
		}
	}
	| value '/' value {
		if (expr(&$$, $1, $3, "div"))
		{
			YYERROR;
		}
	}
	| value '%' value {
		if (expr(&$$, $1, $3, "mod"))
		{
			YYERROR;
		}
	}
	| value '*' value {
		if (expr(&$$, $1, $3, "mul"))
		{
			YYERROR;
		}
	}
	;

%%

int
yyerror (const char *msg)
{
	fprintf(stderr, "%s:%zu: %s\n", filename, lineno, msg);

	errors++;
	return 0;
}

