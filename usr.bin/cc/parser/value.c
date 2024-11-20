#include "../defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
_value (size_t *delta, struct type *type)
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

	// symbol getting
	if (token == SYMBOL)
	{
		struct symbol sym;
		if (getSymbol(yytext, &sym))
		{
			fprintf(stderr, "%s:%zu: Failed to find symbol, `%s' in current context.\n", filename, lineno, yytext);
			errors++;
			token = (enum token)yylex(); // accept SYMBOL
			return 0;
		}

		// found symbol
		switch (sym.type)
		{
		case SYMBOL_VARIABLE:
			token = (enum token)yylex(); // accept SYMBOL
			if (!sym.variable->delta)
			{
				fprintf(stderr, "%s:%zu: Variable `%s' used before set.\n", filename, lineno, sym.variable->name);
				errors++;
				return 0;
			}
			// else, basic variable

			// check if it is being set
			if (token == EQUAL)
			{
				token = (enum token)yylex(); // accept

				if (value(delta, type)) // get the value
				{
					fprintf(stderr, "%s:%zu: Expected a value/expression after equal in variable setting\n", filename, lineno);
					fprintf(stderr, " -> For variable `%s'\n", sym.variable->name);
					errors++;
					return 0;
				}
				// else, got the value back
				// check the type
				if (!compareType(*type, sym.variable->type))
				{
					fprintf(stderr, "%s:%zu: Type miss match when setting variable `%s'\n", filename, lineno, sym.variable->name);
					errors++;
					return 0;
				}
				sym.variable->delta = *delta; // set new delta
				return 0;
			}
			// else just return the symbol
			if (copyType(type, sym.variable->type)) // copy type over
			{
				fprintf(stderr, "%s:%zu: Failed to allocate type information for variable, `%s'\n", filename, lineno, sym.variable->name);
				errors++;
				return 0;
			}
			*delta = sym.variable->delta;
			return 0;
		case SYMBOL_EXTERNAL:
			token = (enum token)yylex(); // accept SYMBOL
			if (copyType(type, sym.external->type)) // copy type over
			{
				fprintf(stderr, "%s:%zu: Failed to allocate type information for external symbol, `%s', dereference.\n", filename, lineno, sym.external->name);
				errors++;
				return 0;
			}
			*delta = ctx->delta++; // new delta

			fputc('\t', yyout);
			printIRType(*type);
			fprintf(yyout, " %%%zu = read_", *delta);
			printIRType(*type);
			fprintf(stdout, " @%s\n", sym.external->name);
			return 0;
		default:
			fprintf(stderr, "%s:%zu: Symbol `%s' is unsupported for evaluation.\n", filename, lineno, yytext);
			errors++;
			token = (enum token)yylex(); // accept SYMBOL
			return 0;
		}
	}

	// integer/immediate tokens
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
			type->base = TYPE_INT;
		}

		token = (enum token)yylex(); // accept
		return 0;
	}

	// '(' value ')'
	if (token == LPAREN)
	{
		token = (enum token)yylex(); // accept

		if (value(delta, type))
		{
			fprintf(stderr, "%s:%zu: Expected a value after left parenthesis.\n", filename, lineno);
			errors++;
			return 0;
		}

		if (token == RPAREN)
		{
			token = (enum token)yylex(); // accept

			return 0;
		}
		// else
		fprintf(stderr, "%s:%zu: Expected a right parenthesis after value.\n", filename, lineno);
		errors++;
		return 0;
	}

	return 1;
}

static int
_term (size_t *delta, struct type *type)
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
	if (_value(&l, &lt)) // left side value
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
		if (_value(&r, &rt)) // if failed
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

	fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
	errors++; // hit EOF
	return 0;
}

static int
_expr (size_t *delta, struct type *type)
{
	// nullify
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
	if (_term(&l, &lt)) // left side value
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
		if (_term(&r, &rt)) // if failed
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

	fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
	errors++; // hit EOF
	return 0;
}

int
value (size_t *delta, struct type *type)
{
	return _expr(delta, type);
}
