#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <stdlib.h>

int
parse_number (long *val)
{
	if (ltok.type != TOK_NUMBER) return 0;

	long v = wcstol(ltok.buf, NULL, 0);
	lex();
	if (val) *val = v;

	return 1;
}
