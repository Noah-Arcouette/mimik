#include "../defs.h"

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

	printType(t);
	fprintf(stderr, "%s\n", yytext);
	freeType(t);

	if (token != SYMBOL)
	{
		fprintf(stderr, "%s:%zu: Expected a symbol name after type.\n", filename, lineno);
		errors++;
		recover();
		return 1;
	}
	token = (enum token)yylex(); // accept

	if (token != SEMICOLON)
	{
		fprintf(stderr, "%s:%zu: Missing semicolon.\n", filename, lineno);
		errors++;
		return 1;
	}
	token = (enum token)yylex();

	return 0;
}
