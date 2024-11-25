#include <stdio.h>
#include "../defs.h"

int
return_ (void)
{
	if (token != RETURN)
	{
		return 1;
	}
	token = (enum token)yylex(); // accept RETURN

	if (!currentFunction)
	{
		fprintf(stderr, "%s:%zu: Error return outside of function.\n", filename, lineno);
		errors++;
		recover();
		return 0;
	}

	size_t      delta;
	struct type t;
	if (!value(&delta, &t)) // return VALUE ;
	{
		fputs("\treturn_", yyout);
		printIRType(t);
		fprintf(yyout, " %%%zu\n\tunreachable\n", delta); // return the delta

		if (!compareType(t, currentFunction->returnType)) // doesn't match the return type
		{
			fprintf(stderr, "%s:%zu: Return type doesn't match returned value.\n", filename, lineno);
			goto return_type_error;
			fprintf(stderr, "\n");
			errors++;
		}
	}
	else // return ;
	{
		fprintf(yyout, "\treturn_void\n\tunreachable\n");

		if (currentFunction->returnType.base != TYPE_VOID) // if a not void return type
		{
			fprintf(stderr, "%s:%zu: Void return in non-void returning function.\n", filename, lineno);
		return_type_error:
			fprintf(stderr, " -> Function defined at line %zu in file `%s'\n", currentFunction->lineno, currentFunction->filename);
			fprintf(stderr, " -> Expected return type: ");
			printType(currentFunction->returnType);
			fprintf(stderr, "\n");
			errors++;
		}
	}
	// goto next block
	fprintf(yyout, "x %zu:\n", ctxLabel++);

	// check for the semicolon
	if (token != SEMICOLON)
	{
		fprintf(stderr, "%s:%zu: Missing semicolon on return statement.\n", filename, lineno);
		errors++;
		return 0;
	}
	token = (enum token)yylex(); // accept
	return 0;
}
