#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../defs.h"
#include "value.h"

int
value_expr (size_t *var, struct type *type)
{
	// nullify
	if (var)
	{
		*var = 0;
	}
	if (type)
	{
		memset(type, 0, sizeof(struct type));
	}

	size_t      l;
	struct type lt;
	if (value_term(&l, &lt)) // left side value
	{
		return 1;
	}

	const char *op;
	size_t      r;
	struct type rt;
	size_t      c;
	while (token != TEOF) // while there is a token
	{
		switch (token)
		{
		case PLUS:
			op = "add";
			break;
		case MINUS:
			op = "sub";
			break;
		default: // return what we already have
			if (var)
			{
				*var = l;
			}
			if (type)
			{
				memcpy(type, &lt, sizeof(struct type));
			}
			else
			{
				freeType(lt);
			}
			return 0;
		}
		token = (enum token)yylex(); // accept the '+'/'-'

		// get right side
		if (value_term(&r, &rt)) // if failed
		{
			fprintf(stderr, "%s:%zu: Expected value on right hand side on operation `%s'\n", filename, lineno, op);
			freeType(lt);
			errors++;
			return 0;
		}

		// check types
		if (!compareType(lt, rt))
		{
			fprintf(stderr, "%s:%zu: Type mismatch on operation `%s'\n", filename, lineno, op);

			fprintf(stderr, " -> Left hand side type: ");
			printType(lt);
			fprintf(stderr, "\n");

			fprintf(stderr, " -> Right hand side type: ");
			printType(rt);
			fprintf(stderr, "\n");

			freeType(lt);
			freeType(rt);

			errors++;
			return 0;
		}

		c = ctxVar++;
		// do the operation
		fprintf(yyout, "\t");
		printIRType(lt);
		fprintf(yyout, " %%%zu = %s_", c, op);
		printIRType(lt);
		fprintf(yyout, " %%%zu %%%zu\n", l, r);

		freeType(rt);

		// update left hand side
		l = c;
	}

	fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
	errors++; // hit EOF
	return 0;
}
