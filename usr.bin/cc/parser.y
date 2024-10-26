%{

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

// lexer
extern int  yylex   (void);
extern void yyerror (const char *);

// tell byacc to not leak memory
#define YY_NO_LEAKS

%}

%token VALUE  // immidiate value
%token SYMBOL // user defined name
%destructor { free($$.string); } SYMBOL

// associativity
%left '+' '-'
%left '/' '%' '*'
%nonassoc UNARY

%start program
%%

program:
	program value ';'
	|
	;

expr:
	'(' value ')'
	// mathamatical
	| value '+' value
	| value '-' value
	| value '/' value
	| value '%' value
	| value '*' value
	| '+' value %prec UNARY
	| '-' value %prec UNARY
	;

args:
	value arg
	|
	;
arg:
	',' value arg
	|
	;

value:
	  VALUE
	| SYMBOL              { free($1.string); }
	| SYMBOL '(' args ')' { free($1.string); }
	| expr
	;

%%

void
yyerror (const char *msg)
{
	errors++;
	fprintf(stderr, "%s:%d: %s\n", filename, lineno, msg);
}

