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
	char *name;
	if (type(&t, &name))
	{
		fprintf(stderr, "%s:%zu: Expected a type after keyword extern.\n", filename, lineno);
		errors++;
		recover();
		return 0;
	}

	if (!name) // make sure there's a name
	{
		freeType(t);
		fprintf(stderr, "%s:%zu: Expected a symbol name after type.\n", filename, lineno);
		errors++;
		recover();
		return 0;
	}

	// function external
	if (token == LPAREN)
	{
		token = (enum token)yylex(); // accept

		// define the function prototype head
		struct prototype *p = definePrototype(t, name, 1);
		if (!p) // failed to acquire a prototype
		{
			freeType(t);
			free(name);
			errors++;
			recover();
			return 0;
		}

		// get parameters
		struct parameter param;
		while (!type(&param.type, &param.name))
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
			freePrototype(p);
			fprintf(stderr, "%s:%zu: Unexpected token before closing parenthesis.\n", filename, lineno);
			errors++;
			recover();
			return 0;
		}
		token = (enum token)yylex(); // accept

		if (token != SEMICOLON)
		{
			freePrototype(p);
			fprintf(stderr, "%s:%zu: Missing semicolon.\n", filename, lineno);
			errors++;
			return 0;
		}
		token = (enum token)yylex(); // accept

		if (doneWithPrototype(p)) // clean up the prototype
		{
			errors++;
		}

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
