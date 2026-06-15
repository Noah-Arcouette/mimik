#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <string.h>

int
parse_label (void)
{
	if (ltok.type != TOK_SYMBOL) return 0;

	if (ltok.size > 256)
	{
		prettyprint("Symbol name to large\n");
		errors++;
		recover();
		return 1;
	}

	// add the symbol
	emitSymbol(ltok.buf);

	lex();

	// colon
	if (ltok.type != TOK_COLON)
	{
		prettyprint("Expected token after loose symbol\n");
		errors++;
		recover();
		return 1;
	}
	lex();

	return 1;
}
