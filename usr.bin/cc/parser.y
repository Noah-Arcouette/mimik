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
%left BOOL_AND BOOL_OR
%left BOOL_EQ BOOL_NEQ BOOL_LTE BOOL_GTE '>' '<'

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
	// boolean operations
	value BOOL_AND value {
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
	fprintf(stderr, "%s:%d: %s.\n", filename, lineno, msg);
}
