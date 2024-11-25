#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../defs.h"
#include "./value.h"

int
value_value (size_t *delta, struct type *typeData)
{
	// nullify returns
	if (delta)
	{
		*delta = 0;
	}
	if (typeData)
	{
		memset(typeData, 0, sizeof(struct type));
	}

	// if definition
	struct symbol sym = { // initialize
		.filename = filename,
		.lineno   = lineno,
		.type     = SYMBOL_VARIABLE
	};
	struct type t;
	if (!type(&t)) // if type
	{
		if (token != SYMBOL) // must be, type symbol . | type symbol eq value
		{
			freeType(t);
			fprintf(stderr, "%s:%zu: Expected symbol after type\n", filename, lineno);
			errors++;
			return 0;
		}
		// define variable
		char *name = strdup(yytext); // duplicate name
		if (!name) // failed to allocate
		{
			fprintf(stderr, "%s:%zu: Failed to allocate name `%s'\n", filename, lineno, yytext);
			freeType(t);
			token = (enum token)yylex(); // accept SYMBOL
			errors++;
			return 0;
		}
		token = (enum token)yylex(); // accept SYMBOL

		sym.variable = defineVariable(name, t); // define
		if (!sym.variable) // failed
		{
			free(name);
			freeType(t);
			errors++;
			return 0;
		}

		if (token == EQUAL)
		{
			goto variable_equ; // handle the variable
		}
		// else
		return 0; // just leave
	}

	// symbol getting
	if (token == SYMBOL)
	{
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

			// check if it is being set
			if (token == EQUAL)
			{
			variable_equ:
				token = (enum token)yylex(); // accept

				if (value(delta, typeData)) // get the value
				{
					fprintf(stderr, "%s:%zu: Expected a value/expression after equal in variable setting\n", filename, lineno);
					fprintf(stderr, " -> For variable `%s'\n", sym.variable->name);
					errors++;
					return 0;
				}
				// else, got the value back
				// check the type
				if (!compareType(*typeData, sym.variable->type))
				{
					fprintf(stderr, "%s:%zu: Type miss match when setting variable `%s'\n", filename, lineno, sym.variable->name);
					errors++;
					return 0;
				}
				sym.variable->delta = *delta; // set new delta
				return 0;
			}
			// else just return the symbol
			if (!sym.variable->delta) // check if used before set
			{
				fprintf(stderr, "%s:%zu: Variable `%s' used before set.\n", filename, lineno, sym.variable->name);
				errors++;
				return 0;
			}
			if (copyType(typeData, sym.variable->type)) // copy type over
			{
				fprintf(stderr, "%s:%zu: Failed to allocate type information for variable, `%s'\n", filename, lineno, sym.variable->name);
				errors++;
				return 0;
			}
			*delta = sym.variable->delta;
			return 0;
		case SYMBOL_EXTERNAL:
			token = (enum token)yylex(); // accept SYMBOL
			if (copyType(typeData, sym.external->type)) // copy type over
			{
				fprintf(stderr, "%s:%zu: Failed to allocate type information for external symbol, `%s', dereference.\n", filename, lineno, sym.external->name);
				errors++;
				return 0;
			}
			*delta = ctx->delta++; // new delta

			fputc('\t', yyout);
			printIRType(*typeData);
			fprintf(yyout, " %%%zu = read_", *delta);
			printIRType(*typeData);
			fprintf(stdout, " @%s\n", sym.external->name);
			return 0;
		default:
			fprintf(stderr, "%s:%zu: Symbol `%s' is unsupported for evaluation.\n", filename, lineno, yytext);
			fprintf(stderr, " -> First seen on line %zu in file `%s'\n", sym.lineno, sym.filename);
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
		if (typeData)
		{
			typeData->base = TYPE_INT;
		}

		token = (enum token)yylex(); // accept
		return 0;
	}

	// '(' value ')'
	if (token == LPAREN)
	{
		token = (enum token)yylex(); // accept

		if (value(delta, typeData))
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
