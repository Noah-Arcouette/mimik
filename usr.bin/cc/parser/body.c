#include "../defs.h"

int
body (void)
{
	if (token != LCURLY)
	{
		return 1;
	}
	token = (enum token)yylex(); // accept

	while (token)
	{
		// leave the body
		if (token == RCURLY)
		{
			token = (enum token)yylex(); // accept
			return 0;
		}

		// value ';'
		if (!value(NULL, NULL))
		{
			if (token != SEMICOLON) // missing semicolon
			{
				fprintf(stderr, "%s:%zu: Expected a semicolon after expression.\n", filename, lineno);
				errors++;
				recover();
				continue;
			}
			token = (enum token)yylex(); // accept
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
