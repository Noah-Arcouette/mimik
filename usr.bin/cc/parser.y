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
%destructor { free($$.string); } SYMBOL STRING

%token VOID CHAR SHORT INT LONG LONG_LONG STRING // types
%token UNSIGNED SIGNED CONST VOLATILE // qualifiers
%token STRUCT UNION ENUM // structure types
%token RETURN IF ELSE EXTERN // keywords
%token EQ NEQ GTE LTE // ==, !=, >=, <= : multicharacter operations

// associativity
%left '+' '-'
%left '/' '%' '*'
%nonassoc UNARY
%right '='
%right EQ NEQ GTE LTE '>' '<'

%start program
%%

program:
	  program line
	| program func line
	|
	;

line:
	  value ';'
	| type SYMBOL ';' { free($2.string); }
	| '{' line line_continue '}'
	// return
	| RETURN value ';'
	| RETURN ';'
	// if/else statements
	| IF '(' value ')' line
	| IF ELSE '(' value ')' line
	| ELSE line
	// extern declarations
	| EXTERN type SYMBOL ';' { free($3.string); }
	| EXTERN func        ';'
	// structural type definitions
	| qualifier struct SYMBOL struct_body pointer ';' { free($3.string); }
	;
line_continue:
	  line line_continue
	|
	;

func:
	type SYMBOL '(' params ')' { free($2.string); }
	;
params:
	  type SYMBOL params_continue { free($2.string); }
	| type        params_continue
	|
	;
params_continue:
	  ',' type SYMBOL params_continue { free($3.string); }
	| ',' type        params_continue
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
	;
struct_body:
	'{' definitions '}'
	;
definitions:
	definition ';' definitions
	|
	;
definition:
	  type SYMBOL array { free($2.string); }
	| type SYMBOL       { free($2.string); }
	| structural
	;
structural:
	  qualifier struct  SYMBOL struct_body pointer { free($3.string); }
	| qualifier struct  SYMBOL             pointer { free($3.string); }
	| qualifier struct         struct_body pointer
	| qualifier ENUM    SYMBOL             pointer { free($3.string); }
	;

type:
	  qualifier         VOID               pointer
	| qualifier signage CHAR               pointer
	| qualifier signage SHORT              pointer
	| qualifier signage INT                pointer
	| qualifier signage LONG               pointer
	| qualifier signage LONG_LONG          pointer
	| structural
	;
array:
	'[' value ']' array_continue
	;
array_continue:
	'[' value ']' array_continue
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
	// compareison
	| value EQ  value
	| value NEQ value
	| value GTE value
	| value LTE value
	| value '>' value
	| value '<' value
	// assignment
	| definition '=' value
	|      SYMBOL '=' value { free($1.string); }
	// indexing
	| SYMBOL array { free($1.string); }
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
	| STRING              { free($1.string); }
	| expr
	// casting
	| '(' type ')' VALUE
	| '(' type ')' SYMBOL              { free($4.string); }
	| '(' type ')' SYMBOL '(' args ')' { free($4.string); }
	| '(' type ')' STRING              { free($4.string); }
	| '(' type ')' '(' value ')'
	;

%%

void
yyerror (const char *msg)
{
	errors++;
	fprintf(stderr, "%s:%d: %s\n", filename, lineno, msg);
}

