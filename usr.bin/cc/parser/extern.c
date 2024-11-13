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
		return 1;
	}

	if (token != SYMBOL)
	{
		freeType(t);
		fprintf(stderr, "%s:%zu: Expected a symbol name after type.\n", filename, lineno);
		errors++;
		recover();
		return 1;
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

	if (token != SEMICOLON)
	{
		freeType(t);
		free(name);
		fprintf(stderr, "%s:%zu: Missing semicolon.\n", filename, lineno);
		errors++;
		return 1;
	}
	token = (enum token)yylex();

	// if all goes good
	if (defineExternal(name, t))
	{
		errors++;
		free(name);
		freeType(t);
		return 1;
	}
	return 0;
}
