#include "../defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
_value (size_t *delta, struct type *type)
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

static int
_expr (size_t *delta, struct type *type)
{
	size_t      l;
	struct type lt;
	if (_value(&l, &lt)) // left side value
	{
		return 1;
	}

	const char *op;
	size_t      r;
	struct type rt;
	size_t      c;
	while (1)
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
		token = (enum token)yylex(); // accept the '+'/'-'

		// get right side
		if (_value(&r, &rt)) // if failed
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

			fprintf(stderr, "%s:%zu: Expected value on right hand side on operation `%s'\n", filename, lineno, op);
			freeType(lt);
			recover();
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
			recover();
			return 0;
		}

		c = ctx->delta++;
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
}

int
value (size_t *delta, struct type *type)
{
	return _expr(delta, type);
}
