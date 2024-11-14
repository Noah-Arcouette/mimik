#include "../defs.h"

int
body (void)
{
	if (token != LCURLY)
	{
		return 1;
	}
	token = (enum token)yylex(); // accept

	while (1)
	{
		// leave the body
		if (token == RCURLY)
		{
			token = (enum token)yylex(); // accept
			return 0;
		}

		// for now, only allow empty bodies

		// unexpected
		fprintf(stderr, "%s:%zu: Unexpected first token in function body.\n", filename, lineno);
		errors++;
		recover();
	}
}
