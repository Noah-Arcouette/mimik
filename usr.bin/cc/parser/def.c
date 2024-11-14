#include "../defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static inline int
_func (struct type t, char *name)
{
	// `('
	if (token != LPAREN)
	{
		return 1; // reject
	}
	token = (enum token)yylex(); // accept

	// create prototype
	struct prototype *p = definePrototype(t, name);
	if (!p)
	{
		freeType(t);
		free(name);
		errors++;
		recover();
		return 0;
	}

	// get, and attach, parameters
	struct parameter param;
	while (!parameter(&param))
	{
		if (defineParameter(p, param))
		{
			freePrototype(p);
			freeParameter(&param);
			errors++;
			recover();
			return 0;
		}

		if (token != COMA) // , param | break
		{
			break;
		}
		token = (enum token)yylex(); // accept the coma
	}

	if (token != RPAREN)
	{
		fprintf(stderr, "%s:%zu: Unexpected token before parenthesis.\n", filename, lineno);
		errors++;
		freePrototype(p);
		recover();
		return 0;
	}
	token = (enum token)yylex(); // accept

	// function fully accepted
	pushContext();
	if (body())
	{
		fprintf(stderr, "%s:%zu: Function expected a body.\n", filename, lineno);
		errors++;
	}
	popContext();

	return 0;
}

int
// type symbol ...
definition (void)
{
	struct type t;
	if (type(&t))
	{
		return 1; // no type, not a defintion
	}

	// accept symbol
	if (token != SYMBOL)
	{
		fprintf(stderr, "%s:%zu: Expected a symbol name after type.\n", filename, lineno);
		recover();
		errors++;
		return 0;
	}
	// save name
	char *name = strdup(yytext);
	if (!name)
	{
		freeType(t);
		fprintf(stderr, "%s:%zu: Failed to allocate symbol name.\n", filename, lineno);
		recover();
		errors++;
		return 0;
	}
	// accept
	token = (enum token)yylex();

	// check if function
	if (!_func(t, name))
	{
		return 0;
	}

	// check if variable
	//  -> just fail for now
	freeType(t);
	free(name);
	fprintf(stderr, "%s:%zu: Unexpected after symbol name.\n", filename, lineno);
	recover();
	errors++;

	return 0;
}
