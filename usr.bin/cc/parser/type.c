#include "../defs.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// cannot failed safely, if called a pointer shall ALWAYS be there
static int
_pointerType (struct type *t)
{
	token = (enum token)yylex(); // accept the STAR

	struct type point;
	memset(&point, 0, sizeof(struct type));
	point.base = TYPE_POINTER;

	// allocate and attach original base type
	point.down = (struct type *)malloc(sizeof(struct type));
	if (!point.down) // failed to allocate
	{
		int errnum = errno;
		fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
		fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
		return 1;
	}
	memcpy(point.down, t, sizeof(struct type));
	memcpy(t,     &point, sizeof(struct type));

	// qualifiers
	while (token)
	{
		switch (token)
		{
		// UNSIGNED, SIGNED, and LONG are not allow on pointers
		case CONST:
			t->isConst = 1;
			break;
		case RESTRICT:
			t->isRestrict = 1;
			break;
		default:
			return 0; // just leave
		}

		token = (enum token)yylex();
	}

	fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
	errors++;
	return 0; // hit EOF
}

// cannot failed safely, if called an array shall ALWAYS be there
static int
_arrayType (struct type *t)
{
	token = (enum token)yylex(); // accept the LSQUARE

	struct type point;
	memset(&point, 0, sizeof(struct type));
	point.base    = TYPE_POINTER;
	point.isConst = 1;

	// get the bounds, if any
	value(&point.bounding, NULL);

	// allocate and attach original base type
	point.down = (struct type *)malloc(sizeof(struct type));
	if (!point.down) // failed to allocate
	{
		int errnum = errno;
		fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
		fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
		return 1;
	}

	// closing bracket
	if (token != RSQUARE)
	{
		fprintf(stderr, "%s:%zu: Expected a closing square bracket in array definition.\n", filename, lineno);
		errors++;
	}
	else
	{
		// accept the token
		token = (enum token)yylex();
	}

	memcpy(point.down, t, sizeof(struct type));
	memcpy(t,     &point, sizeof(struct type));

	return 0;
}

int
type (struct type *t, char **name)
{
	memset(t, 0, sizeof(struct type));
	*name = (char *)NULL; // nullify

	// qualifiers
	while (1)
	{
		switch (token)
		{
		case TEOF:
			fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
			errors++;
			return 0; // hit EOF
		case UNSIGNED:
			t->isUnsigned = 1;
			break;
		case SIGNED:
			t->isUnsigned = 0;
			break;
		case LONG:
			t->longness++;
			break;
		case CONST:
			t->isConst = 1;
			break;
		// restrict isn't allowed on base types
		default:
			goto leave;
		}

		token = (enum token)yylex();
	}
leave:

	// base type
	switch (token)
	{
	case TEOF:
		fprintf(stderr, "%s:%zu: Unexpected EOF.\n", filename, lineno);
		errors++;
		return 0; // hit EOF
	case VOID:
		t->base = TYPE_VOID;
		break;
	case CHAR:
		t->base = TYPE_CHAR;
		break;
	case SHORT:
		t->base = TYPE_SHORT;
		break;
	case INT:
		t->base = TYPE_INT;
		break;
	default:
		return 1;
	}
	token = (enum token)yylex();

	// check for pointer
	while (token == STAR)
	{
		if (_pointerType(t))
		{
			freeType(*t);
			return 0;
		}
	}

	// check for a name/symbol
	if (token == SYMBOL)
	{
		*name = strdup(yytext); // copy the name

		// make sure the name got copied
		if (!(*name))
		{
			fprintf(stderr, "%s:%zu: Failed to allocate symbol name, `%s', after type\n", filename, lineno, yytext);
			errors++;
		}

		// accept the name
		token = (enum token)yylex();
	}

	// check for arrays
	while (token == LSQUARE)
	{
		if (_arrayType(t))
		{
			freeType(*t);
			return 0;
		}
	}

	return 0;
}
