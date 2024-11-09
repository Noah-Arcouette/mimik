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
%token VALUE SYMBOL
%token INT // Types

// associatiity
%left '+' '-'
%left '*' '/' '%'

%left '>' '<' GTE LTE EQU NEQ
%left '&' '|' '^'
%left BOOL_AND BOOL_OR

%start program
%destructor {
	free($$.string);
	$$.string = (char *)NULL;
} SYMBOL
%%

program:
	  program value  ';'
	| program define ';'
	|
	;

// definition
define:
	type SYMBOL {
		if (defineVar($2.string, $1.type))
		{
			free($2.string);
			errors++;
			YYERROR;
		}
	}
	;
// types
type:
	INT {
		memset(&$$, 0, sizeof(struct value));
		$$.type.base = TYPE_INT;
	}
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
	// bitwise operations
	| value '&' value {
		if (expr(&$$, $1, $3, "and"))
		{
			YYERROR;
		}
	}
	| value '|' value {
		if (expr(&$$, $1, $3, "or"))
		{
			YYERROR;
		}
	}
	| value '^' value {
		if (expr(&$$, $1, $3, "xor"))
		{
			YYERROR;
		}
	}
	// comparisons
	| value '>' value {
		if (boolExpr(&$$, $1, $3, "gt"))
		{
			YYERROR;
		}
	}
	| value '<' value {
		if (boolExpr(&$$, $1, $3, "lt"))
		{
			YYERROR;
		}
	}
	| value GTE value {
		if (boolExpr(&$$, $1, $3, "gte"))
		{
			YYERROR;
		}
	}
	| value LTE value {
		if (boolExpr(&$$, $1, $3, "lte"))
		{
			YYERROR;
		}
	}
	| value EQU value {
		if (boolExpr(&$$, $1, $3, "equ"))
		{
			YYERROR;
		}
	}
	| value NEQ value {
		if (boolExpr(&$$, $1, $3, "neq"))
		{
			YYERROR;
		}
	}
	| value BOOL_AND value {
		if (expr(&$$, $1, $3, "and"))
		{
			YYERROR;
		}
	}
	| value BOOL_OR value {
		if (expr(&$$, $1, $3, "or"))
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

