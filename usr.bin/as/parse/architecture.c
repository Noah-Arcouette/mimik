#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <libintl.h>

int
parse_architecture (void)
{
	// .arch
	if (ltok.type != TOK_ARCH) return 0;
	lex();

	// symbol
	if (ltok.type != TOK_SYMBOL)
	{
		prettyprint(gettext("Expected a symbol\n"));
		recover();
		errors++;
		return 1;
	}
	setArch(ltok.buf);
	lex();

	// newline
	if (ltok.type != TOK_NEWLINE)
	{
		prettyprint(gettext("Expected a newline\n"));
		recover();
		errors++;
	}
	else // so we don't consume anything twice
	{
		lex();
	}
	return 1;
}
