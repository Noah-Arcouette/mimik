#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <string.h>

int
parse_x86_16_jmp (void)
{
	if (ltok.type != TOK_SYMBOL) return 0;
	// symbol

	// sjmp
	if (!strcmp(ltok.buf, "sjmp"))
	{
		lex();

		// symbol
		if (ltok.type != TOK_SYMBOL)
		{
			prettyprint("Expected a symbol\n");
			errors++;
			recover();
			return 1;
		}

		// emit the data
		char buf = 0b11101011;
		emit(&buf, 1);

		emitGap(ltok.buf, MIO_GAP_TYPE_DISP_BYTE);

		lex();
		return 1;
	}

	return 0;
}
