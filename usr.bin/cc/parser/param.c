#include "../defs.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int
parameter (struct parameter *p)
{
	// type name?
	if (type(&p->type))
	{
		return 1;
	}

	if (token == SYMBOL) // if not defined it's still okay
	{
		p->name = strdup(yytext);
		if (!p->name)
		{
			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate memory for parameter name.\n", filename, lineno);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
			errors++; // report error
			// it's okay, maybe, the variable may not be defined though
		}
		token = (enum token)yylex(); // accept
	}
	else
	{
		p->name = (char *)NULL; // make sure it gets null
		// or un-name variable will get a name carried over via prior named variable
		// this will cause a double free so please do this
	}

	return 0;
}
