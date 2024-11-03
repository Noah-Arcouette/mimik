%{

#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define YY_NO_LEAKS // tell yacc to free its data
%}

%token VALUE // immediate value
%token SYMBOL // symbol
%destructor { free($$.symbol); } SYMBOL

// binary operations
%left '+' '-'
%left '/' '%' '*'
%left '&' '|' '^'
%left BOOL_AND BOOL_OR
%left BOOL_EQ BOOL_NEQ BOOL_LTE BOOL_GTE '>' '<'
// unary
%right UNARY
// assigment
%right '='

// types
%token VOID CHAR SHORT INT
// qualifiers
%token EXTERN CONST

%start program
%%

program:
	  program value  ';' { addNode(&root, &$2); }
	| program define ';' { addNode(&root, &$2); }
	| program extern ';' { addNode(&root, &$2); }
	| program error  ';' { yyerrok; yyclearin; }
	| // empty
	;

// external definitions
extern:
	EXTERN define {
		memcpy(&$$, &$2, sizeof(struct node));
		$$.nodeType = NODE_EXTERN_DEFINE;
	}
	;

type:
	CONST type {
		memcpy(&$$, &$2, sizeof(struct node));
		$$.valueType.isConst = 1;
	}
	| VOID {
		memset(&$$, 0, sizeof(struct node));
		$$.valueType.type     = TYPE_VOID;
		$$.valueType.signness = 1;
	}
	| CHAR {
		memset(&$$, 0, sizeof(struct node));
		$$.valueType.type     = TYPE_CHAR;
		$$.valueType.signness = 1;
	}
	| SHORT {
		memset(&$$, 0, sizeof(struct node));
		$$.valueType.type     = TYPE_SHORT;
		$$.valueType.signness = 1;
	}
	| INT {
		memset(&$$, 0, sizeof(struct node));
		$$.valueType.type     = TYPE_INT;
		$$.valueType.signness = 1;
	}
	;

// definition
define:
	type SYMBOL {
		memcpy(&$$, &$1, sizeof(struct node)); // give it the type of the type
		$$.nodeType = NODE_DEFINE;
		$$.symbol   = strdup($2.symbol); // give it the symbol from the symbol
		if (!$$.symbol)
		{
			int errnum = errno;
			fprintf(stderr, "%s: Failed to allocate memory.\n", self);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
			exit(1);
		}
		free($2.symbol);
	}
	;
// immediate value
value:
	VALUE { memcpy(&$$, &$1, sizeof(struct node)); }
	| expr
	// assignment
	| SYMBOL '=' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_ASSIGN;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| define '=' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_ASSIGN;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	;
expr: // expressions
	// unary oparations
	'-' value %prec UNARY {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_NEG;
		addNode(&$$, &$2);
	}
	| '+' value %prec UNARY {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_POS;
		addNode(&$$, &$2);
	}
	| '~' value %prec UNARY {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_NOT;
		addNode(&$$, &$2);
	}
	| '!' value %prec UNARY {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_NOT;
		addNode(&$$, &$2);
	}
	// boolean operations
	| value BOOL_AND value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_AND;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value BOOL_OR value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_OR;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value BOOL_EQ value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_EQ;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value BOOL_NEQ value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_NEQ;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value BOOL_GTE value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_GTE;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value BOOL_LTE value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_LTE;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '>' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_GT;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '<' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_BOOL_LT;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	// binary arithmetic
	| value '&' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_AND;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '|' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_OR;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '^' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_XOR;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	// simple math
	| value '+' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_ADD;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '-' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_SUB;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '/' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_DIV;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '%' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_MOD;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| value '*' value {
		memset(&$$, 0, sizeof(struct node));
		$$.nodeType = NODE_MUL;
		addNode(&$$, &$1);
		addNode(&$$, &$3);
	}
	| '(' value ')' { memcpy(&$$, &$2, sizeof(struct node)); }
	;

%%

void
yyerror (const char *msg)
{
	errors++;
	fprintf(stderr, "%s:%d: %s.\n", filename, lineno, msg);
}
