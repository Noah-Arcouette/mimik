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

%token VALUE STRING // immidiate value
%token SYMBOL // user defined name
%destructor { free($$.string); } SYMBOL STRING

%token ELLIPSIS
%token VOID CHAR SHORT INT  // types
%token UNSIGNED SIGNED CONST VOLATILE LONG // qualifiers
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
	  external   program
	| definition program
	| function   program
	| error program { yyerrok; yyclearin; }
	|
	;

// definition, and assignment
definition:
	  type SYMBOL array ';' { free($2.string); }
	| type SYMBOL ';'       { free($2.string); }
	// with assignment
	| type SYMBOL       '=' value ';' { free($2.string); }
	| type SYMBOL array '=' value ';' { free($2.string); }
	// structures and unions
	| structure
	;
array:
	'[' value ']' array_continue
	;
array_continue:
	array
	|
	;

// structure
structure:
	  struct SYMBOL struct_body ';' { free($2.string); }
	| struct        struct_body ';'
	;
struct:
	  STRUCT
	| UNION
	;
struct_body:
	'{' struct_elements '}'
	;
struct_elements:
	  definition struct_elements
	|
	;

// externals
external:
	  EXTERN type SYMBOL   ';' { free($3.string); }
	| EXTERN function_head ';'
	;

// function
function:
	function_head body
function_head:
	type SYMBOL '(' function_params ')' { free($2.string); }
	;
function_params:
	  type        function_params_continue
	| type SYMBOL function_params_continue { free($2.string); }
	|
	;
function_params_continue:
	  ',' function_params
	| ',' ELLIPSIS
	|
	;

// execution body
body:
	  '{' body_continue '}'
	| definition
	// if statement
	|      IF '(' value ')' body
	| ELSE                  body
	// just a value
	| value ';'
	// return
	| RETURN value ';'
	| RETURN ';'
	;
body_continue:
	body body_continue
	|
	;

// variable type
type:
	  qualifiers number_qualifiers number pointer
	| qualifiers                   VOID   pointer
	;
qualifiers: // general type qualifiers
	  CONST    qualifiers
	| VOLATILE qualifiers
	|
	;
number_qualifiers: // qualifiers for integer types
	  UNSIGNED number_qualifiers
	| SIGNED   number_qualifiers
	| LONG     number_qualifiers
	|
	;
number: // general number types
	  CHAR
	| SHORT
	| INT
	;
pointer:
	qualifiers '*' pointer
	|
	;

// value
value:
	  VALUE
	| STRING { free($1.string); }
	| expr
	// symbols get and set
	| SYMBOL           { free($1.string); }
	| SYMBOL '=' value { free($1.string); }
	// array indexing
	| SYMBOL array { free($1.string); }
	// function call
	| SYMBOL '(' ')' { free($1.string); }
	;
// expression
expr:
	// math
	  value '+' value
	| value '-' value
	| value '/' value
	| value '%' value
	| value '*' value
	// comparisons
	| value '>' value
	| value '<' value
	| value EQ  value
	| value NEQ value
	| value GTE value
	| value LTE value
	;

%%

void
yyerror (const char *msg)
{
	errors++;
	fprintf(stderr, "%s:%d: %s\n", filename, lineno, msg);
}

