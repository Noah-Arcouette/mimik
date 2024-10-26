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

// types
%token CHAR SHORT INT LONG LONG_LONG
%token UNSIGNED SIGNED CONST VOLATILE // qualifiers
%token STRUCT UNION ENUM // structure types

// associativity
%left '+' '-'
%left '/' '%' '*'
%nonassoc UNARY
%right '='

%start program
%%

program:
	  program value ';'
	| program type SYMBOL ';' { free($3.string); }
	|
	;

qualifier:
	  CONST qualifier
	| VOLATILE qualifier
	|
	;
pointer:
	qualifier '*' pointer
	|
	;
signage:
	  UNSIGNED
	|   SIGNED
	|
	;
struct:
	  STRUCT
	| UNION
	| ENUM
	;
type:
	  qualifier signage CHAR pointer
	| qualifier signage SHORT pointer
	| qualifier signage INT pointer
	| qualifier signage LONG pointer
	| qualifier signage LONG_LONG pointer
	| qualifier struct  SYMBOL pointer { free($3.string); }
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
	// assignment
	| type SYMBOL '=' value { free($2.string); }
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

