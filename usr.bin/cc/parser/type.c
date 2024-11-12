#include "../defs.h"

int
type (struct type *t)
{
	switch (token)
	{
	case INT:
		token = (enum token)yylex();
		t->base = TYPE_INT;
		return 0;
	default:
		return 1;
	}
}
