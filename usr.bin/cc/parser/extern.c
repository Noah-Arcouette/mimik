#include "../defs.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int
extern_ (void)
{
	if (token != EXTERN)
	{
		return 1;
	}
	token = (enum token)yylex(); // accept

	struct type t;
	if (type(&t))
	{
		fprintf(stderr, "%s:%zu: Expected a type after keyword extern.\n", filename, lineno);
		errors++;
		recover();
		return 0;
	}

	if (token != SYMBOL)
	{
		freeType(t);
		fprintf(stderr, "%s:%zu: Expected a symbol name after type.\n", filename, lineno);
		errors++;
		recover();
		return 0;
	}
	char *name = strdup(yytext); // get a duplicate of the name
	if (!name) // failed to allocate
	{
		freeType(t);
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
	token = (enum token)yylex(); // accept

	// function external
	if (token == LPAREN)
	{
		token = (enum token)yylex();
		if (token != RPAREN)
		{
			freeType(t);
			free(name);
			fprintf(stderr, "%s:%zu: Missing closing parenthesis.\n", filename, lineno);
			errors++;
			recover();
			return 0;
		}
		token = (enum token)yylex();

		// define the function prototype head
		struct prototype *p = definePrototype(t, name);
		if (!p) // failed to acquire a prototype
		{
			freeType(t);
			free(name);
			errors++;
			recover();
			return 0;
		}

		// get parameters
		// type name? [, type name?]* : the parameters may not have names

		if (token != SEMICOLON)
		{
			freePrototype(p);
			fprintf(stderr, "%s:%zu: Missing semicolon.\n", filename, lineno);
			errors++;
			return 0;
		}
		token = (enum token)yylex();
		return 0;
	}

	// variable external
	if (token != SEMICOLON)
	{
		freeType(t);
		free(name);
		fprintf(stderr, "%s:%zu: Missing semicolon.\n", filename, lineno);
		errors++;
		return 0;
	}
	token = (enum token)yylex();

	// if all goes good
	lineno--;
	if (defineExternal(name, t))
	{
		errors++;
		free(name);
		freeType(t);
	}

	lineno++;
	return 0;
}
