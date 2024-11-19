#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum dataType dataType = ILP32; // 32bit by default

void
printType (struct type t)
{
	if (t.base == TYPE_POINTER)
	{
		printType(*t.down);

		fprintf(stderr, "* ");
	}

	if (t.isConst)
	{
		fprintf(stderr, "const ");
	}
	if (t.isRestrict)
	{
		fprintf(stderr, "restrict ");
	}
	if (t.isUnsigned)
	{
		fprintf(stderr, "unsigned ");
	}
	while (t.longness--)
	{
		fprintf(stderr, "long ");
	}

	switch (t.base)
	{
	case TYPE_VOID:
		fprintf(stderr, "void");
		break;
	case TYPE_CHAR:
		fprintf(stderr, "char");
		break;
	case TYPE_SHORT:
		fprintf(stderr, "short");
		break;
	case TYPE_INT:
		fprintf(stderr, "int");
		break;
	case TYPE_POINTER:
		break;
	}
}

void
printIRType (struct type t)
{
	int size;
	switch (t.base)
	{
	case TYPE_VOID:
		fprintf(yyout, "void");
		break;
	case TYPE_CHAR:
		fprintf(yyout, "%c8",
			t.isUnsigned ? 'u' : 'i');
		break;
	case TYPE_SHORT:
		fprintf(yyout, "%c16",
			t.isUnsigned ? 'u' : 'i');
		break;
	case TYPE_INT:
		size = 32;
		switch (dataType)
		{
		case LP64:
			if (t.longness)
			{
				size = 64;
			}
			break;
		case ILP64:
			size = 64;
			break;
		case LLP64:
			if (t.longness > 1)
			{
				size = 64;
			}
			break;
		case ILP32: // always 32bit
			break;
		case LP32:
			size = 16;
			if (t.longness)
			{
				size = 32;
			}
			break;
		}

		fprintf(yyout, "%c%d",
			t.isUnsigned ? 'u' : 'i',
			size);
		break;
	case TYPE_POINTER:
		size = 64;
		switch (dataType)
		{
		case ILP32:
		case LP32:
			size = 32;
			break;
		default:
			break; // keep 64
		}
		fprintf(yyout, "%c%d",
			t.isUnsigned ? 'u' : 'i',
			size);
		break;
	}
}

void
freeType (struct type t)
{
	struct type *p = t.down; // pointer part
	struct type *d; // down
	while (p) // while there's a pointer
	{
		d = p->down; // save down
		free(p); // free
		p = d; // move
	}
}

int
// check if types are a exact match
compareType (struct type a, struct type b)
{
	// if pointers
	if (a.base == TYPE_POINTER && b.base == TYPE_POINTER)
	{
		if (!compareType(*(a.down), *(b.down))) // compare the next type
		{
			return 0; // failed
		}
		// set to null
		a.down = (struct type *)NULL;
		b.down = (struct type *)NULL;
	}

	// compare
	return !memcmp(&a, &b, sizeof(struct type));
}

int
copyType (struct type *dest, struct type src)
{
	memcpy(dest, &src, sizeof(struct type));

	// copy the pointer recursively
	if (src.base == TYPE_POINTER)
	{
		// allocate the down
		dest->down = (struct type *)malloc(sizeof(struct type));
		if (!dest->down)
		{
			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate type data while copying type.\n", filename, lineno);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
			return 1;
		}

		// copy the down
		if (copyType(dest->down, *src.down))
		{
			free(dest->down);
			dest->down = (struct type *)NULL;
			return 1;
		}
	}

	return 0;
}
