#include "../defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
value (size_t *delta, struct type *type)
{
	if (token == IMM_INT)
	{
		size_t c = ctx->delta++;
		fprintf(yyout, "\ti32 %%%zu = %s\n", c, yytext);

		if (delta)
		{
			*delta = c;
		}
		if (type)
		{
			memset(type, 0, sizeof(struct type)); // nullify
			type->base = TYPE_INT;
		}

		token = (enum token)yylex(); // accept
		return 0;
	}

	return 1;
}
