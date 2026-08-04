#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_interrupt (void)
{
	if (ltok.type != TOK_SYMBOL || strcmp("int", ltok.buf))
	{
		return 0;
	}
	lex();

	// the interrupt vector
	long vector;
	if (!parse_number(&vector))
	{
		prettyprint(gettext("Expected a number\n"));
		errors++;
		recover();
		return 1;
	}

	// int3
	if (vector == 3)
	{
		char inst[1] = { 0b11001100 };
		emit(inst, 1);
		return 1;
	}

	char inst[2] = { 0b11001101, vector&0xff };
	emit(inst, 2);
	return 1;
}
