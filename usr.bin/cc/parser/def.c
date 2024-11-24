#include "../defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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
	struct prototype *p = definePrototype(t, name, 0);
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

	if (doneWithPrototype(p)) // clean up the prototype
	{
		errors++;
		freePrototype(p);
		recover();
		return 0;
	}

	// function fully accepted
	pushContext();
	currentFunction = p;

	// define label
	fprintf(yyout, "gx %s (", p->name);

	// bring the parameters into context
	struct variable *v;
	char       *paramName;
	struct type paramType;
	for (size_t i = 0; i<p->parameters; i++)
	{
		if (!p->parameter[i].name)
		{
			continue;
		}

		// duplicate name and type for definition
		paramName = strdup(p->parameter[i].name);
		if (!paramName) // failed
		{
			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate parameter name, for parameter %zu, `%s'.\n", filename, lineno, i+1, p->parameter[i].name);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
			errors++;
			continue; // skip it
		}

		if (copyType(&paramType, p->parameter[i].type))
		{
			fprintf(stderr, " -> For parameter %zu, `%s'\n", i+1, paramName);
			errors++;
			free(paramName);
			continue; // skip it
		}

		v = defineVariable(paramName, paramType);
		if (!v) // failed to define variable
		{
			fprintf(stderr, " -> For parameter %zu, `%s'\n", i+1, paramName);
			free(paramName);
			freeType(paramType);
			errors++;
			continue; // skip it
		}
		v->delta = ctx->delta++; // set the variables delta

		fputc(' ', yyout);
		printIRType(v->type);
		fprintf(yyout, " %%%zu", v->delta);
	}
	fprintf(yyout, " ): \n");

	if (body())
	{
		fprintf(stderr, "%s:%zu: Function expected a body.\n", filename, lineno);
		errors++;
	}

	currentFunction = (struct prototype *)NULL; // don't worry about nesting because functions can't nest
	popContext();

	// if void, add implicit return
	if (p->returnType.base == TYPE_VOID)
	{
		fprintf(yyout, "\treturn_void\n");
	}

	// end of a function should always be unreachable
	fprintf(yyout, "\tunreachable\n");

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
