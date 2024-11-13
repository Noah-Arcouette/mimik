#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

void
printType (struct type t)
{
	if (t.base == TYPE_POINTER)
	{
		printType(*t.down);

		fprintf(stderr, "* ");
	}

	if (t.isVolatile)
	{
		fprintf(stderr, "volatile ");
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
