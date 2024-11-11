%{
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t temps = 1; // variable of 0 is undefined

int errors = 0;

#define YY_NO_LEAKS
%}

// immediate values
%token GOTO
%token VALUE SYMBOL
%token INT // Types

// associatiity
%right '='

%left '+' '-'
%left '*' '/' '%'

%left '>' '<' GTE LTE EQU NEQ
%left '&' '|' '^'
%left BOOL_AND BOOL_OR
%right UNARY

%start program
%destructor {
	free($$.string);
	$$.string = (char *)NULL;
} SYMBOL
%%

program:
	  program value  ';'
	| program define ';'
	| program body_open program body_close
	| program SYMBOL ':' {
		// label definition
		if (defineLabel($2.string)) // if failed
		{
			errors++;
			YYERROR;
		}
	}
	| program GOTO SYMBOL ';' {
		gotoLabel($3.string);
	}
	|
	;
// body '{' '}'
// evaluate separately so the actions can be wrapped acordingly
body_open:
	'{' {
		pushContext();
	}
	;
body_close:
	'}' {
		if (popContext())
		{
			errors++;
			YYERROR;
		}
	}
	;

// definition
define:
	type SYMBOL {
		if (!defineVar($2.string, $1.type))
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
	| SYMBOL {
		struct variable *v = getVar($1.string);

		if (!v) // no variable
		{
			fprintf(stderr, "%s:%zu: Variable `%s' does not exist.\n", filename, lineno, $1.string);
		value_error:
			free($1.string);
			errors++;
			YYERROR;
			// yyerror should break
		}

		// variable has no delta, used before set
		if (!v->delta)
		{
			fprintf(stderr, "%s:%zu: Variable `%s' used before a value was set.\n", filename, lineno, $1.string);
			goto value_error;
		}

		free($1.string);

		$$.variable = 1;
		$$.value    = (unsigned long long int)v->delta;
		memcpy(&$$.type, &v->type, sizeof(struct type));
	}
	// variable setting
	| SYMBOL '=' value {
		struct variable *v = getVar($1.string);
		free($1.string);

		if (setVar(v, $3))
		{
			errors++;
			YYERROR;
			// yyerror should break
		}

		$$.variable = 1;
		$$.value    = (unsigned long long int)v->delta;
		memcpy(&$$.type, &v->type, sizeof(struct type));
	}
	| type SYMBOL '=' value {
		struct variable *v;
		if (!(v = defineVar($2.string, $1.type)))
		{
			free($2.string);
			errors++;
			YYERROR;
		}

		if (setVar(v, $4))
		{
			errors++;
			YYERROR;
			// yyerror should break
		}

		$$.variable = 1;
		$$.value    = (unsigned long long int)v->delta;
		memcpy(&$$.type, &v->type, sizeof(struct type));
	}
	;
expr:
	'(' value ')' {
		memcpy(&$$, &$2, sizeof(struct value));
	}
	// bitwise operations
	| value '&' value {
		if (expr(&$$, $1, $3, "and"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '|' value {
		if (expr(&$$, $1, $3, "or"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '^' value {
		if (expr(&$$, $1, $3, "xor"))
		{
			errors++;
			YYERROR;
		}
	}
	| '~' value %prec UNARY {
		unaryExpr(&$$, $2, "not");
	}
	// comparisons
	| '!' value %prec UNARY {
		struct value v;
		memset(&v, 0, sizeof(struct value));
		v.type.base = TYPE_INT;

		if (boolExpr(&$$, $2, v, "eq"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '>' value {
		if (boolExpr(&$$, $1, $3, "gt"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '<' value {
		if (boolExpr(&$$, $1, $3, "lt"))
		{
			errors++;
			YYERROR;
		}
	}
	| value GTE value {
		if (boolExpr(&$$, $1, $3, "gte"))
		{
			errors++;
			YYERROR;
		}
	}
	| value LTE value {
		if (boolExpr(&$$, $1, $3, "lte"))
		{
			errors++;
			YYERROR;
		}
	}
	| value EQU value {
		if (boolExpr(&$$, $1, $3, "equ"))
		{
			errors++;
			YYERROR;
		}
	}
	| value NEQ value {
		if (boolExpr(&$$, $1, $3, "neq"))
		{
			errors++;
			YYERROR;
		}
	}
	| value BOOL_AND value {
		if (expr(&$$, $1, $3, "and"))
		{
			errors++;
			YYERROR;
		}
	}
	| value BOOL_OR value {
		if (expr(&$$, $1, $3, "or"))
		{
			errors++;
			YYERROR;
		}
	}
	// basic math operations
	| value '+' value {
		if (expr(&$$, $1, $3, "add"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '-' value {
		if (expr(&$$, $1, $3, "sub"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '/' value {
		if (expr(&$$, $1, $3, "div"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '%' value {
		if (expr(&$$, $1, $3, "mod"))
		{
			errors++;
			YYERROR;
		}
	}
	| value '*' value {
		if (expr(&$$, $1, $3, "mul"))
		{
			errors++;
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

