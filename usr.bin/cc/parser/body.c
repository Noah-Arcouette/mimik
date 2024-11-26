#include "../defs.h"

static int
_line (void)
{
	// value ';'
	if (!value(NULL, NULL))
	{
		if (token != SEMICOLON) // missing semicolon
		{
			fprintf(stderr, "%s:%zu: Expected a semicolon after expression.\n", filename, lineno);
			errors++;
			recover();
			return 0;
		}
		token = (enum token)yylex(); // accept
		return 0;
	}

	// return value? ;
	if (!return_())
	{
		return 0;
	}

	// if ( value ) body
	if (!if_())
	{
		return 0;
	}

	// while ( value ) body
	if (!while_())
	{
		return 0;
	}

	// { ... }
	if (token == LCURLY)
	{
		pushContext();
		body();
		popContext();
		return 0;
	}

	return 1;
}

int
body (void)
{
	if (token != LCURLY)
	{
		if (_line())
		{
			fprintf(stderr, "%s:%zu: Unexpected first token in body.\n", filename, lineno);
			errors++;
			return 1;
		}
		return 0;
	}
	token = (enum token)yylex(); // accept

	while (token != TEOF) // while there is a token
	{
		// leave the body
		if (token == RCURLY)
		{
			token = (enum token)yylex(); // accept
			return 0;
		}

		if (!_line())
		{
			continue;
		}

		// { ... }
		if (token == LCURLY)
		{
			pushContext();
			body();
			popContext();
			continue;
		}

		// unexpected
		fprintf(stderr, "%s:%zu: Unexpected first token in function body.\n", filename, lineno);
		errors++;
		recover();
	}


	fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
	errors++;
	return 0; // hit EOF
}
