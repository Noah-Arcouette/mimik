#include "../defs.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

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
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
	memcpy(point.down, t, sizeof(struct type));
	memcpy(t,     &point, sizeof(struct type));

	// qualifiers
	while (1)
	{
		switch (token)
		{
		case UNSIGNED:
			t->isUnsigned = 0;
			break;
		case SIGNED:
			t->isUnsigned = 0;
			break;
		case LONG:
			t->longness++;
			break;
		case VOLATILE:
			t->isVolatile = 1;
			break;
		case CONST:
			t->isConst = 1;
			break;
		case RESTRICT:
			t->isRestrict = 1;
			break;
		default:
			return 1;
		}

		token = (enum token)yylex();
	}
}

int
type (struct type *t)
{
	memset(t, 0, sizeof(struct type));
	// qualifiers
	while (1)
	{
		switch (token)
		{
		case UNSIGNED:
			t->isUnsigned = 0;
			break;
		case SIGNED:
			t->isUnsigned = 0;
			break;
		case LONG:
			t->longness++;
			break;
		case VOLATILE:
			t->isVolatile = 1;
			break;
		case CONST:
			t->isConst = 1;
			break;
		case RESTRICT:
			t->isRestrict = 1;
			break;
		default:
			goto leave;
		}

		token = (enum token)yylex();
	}
leave:

	// base type
	switch (token)
	{
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
		_pointerType(t);
	}

	return 0;
}
