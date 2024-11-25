#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../defs.h"
#include "value.h"

int
value_term (size_t *delta, struct type *type)
{
	// nullify returns
	if (delta)
	{
		*delta = 0;
	}
	if (type)
	{
		memset(type, 0, sizeof(struct type));
	}

	size_t      l;
	struct type lt;
	if (value_value(&l, &lt)) // left side value
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
		case STAR:
			op = "mul";
			break;
		case DIV:
			op = "div";
			break;
		case MOD:
			op = "mod";
			break;
		default: // return what we already have
			if (delta)
			{
				*delta = l;
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
		token = (enum token)yylex(); // accept the '*'/'/'/'%'

		// get right side
		if (value_value(&r, &rt)) // if failed
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

		c = ctxDelta++;
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
