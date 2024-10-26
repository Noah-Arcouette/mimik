%{

#include <stdio.h>
#include "defs.h"

// lexer
extern int  yylex   (void);
extern void yyerror (const char *);

// tell byacc to not leak memory
#define YY_NO_LEAKS

%}

%token VALUE // immidiate value

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

value:
	VALUE
	| expr
	;

%%

void
yyerror (const char *msg)
{
	errors++;
	fprintf(stderr, "%s:%d: %s\n", filename, lineno, msg);
}

