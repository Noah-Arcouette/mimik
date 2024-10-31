%{

#include "defs.h"
#include <stdio.h>
#include <string.h>

#define YY_NO_LEAKS // tell yacc to free its data
%}

%token VALUE // immediate value

// binary operations
//  simple math
%left '+' '-'
%left '/' '%' '*'
%left '&' '|' '^'

%start program
%%

program:
	program value ';' { addNode(&root, &$2); }
	| // empty
	;

// immediate value
value:
	VALUE { memcpy(&$$, &$1, sizeof(struct node)); }
	| expr
	;
expr: // expressions
	// binary arithmetic
	value '&' value {
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
	fprintf(stderr, "%s:%d: %s.\n", filename, lineno, msg);
}
