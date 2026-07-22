#include "../parse.h"
#include "../main.h"
#include "../lex.h"

int
parse_entry (void)
{
	if (ltoken.type != LTYPE_ENTRY) return 0;
	lex();

	// (
	if (ltoken.type != LTYPE_OPEN_PAREN)
	{
		prettyprint("Expected an opening bracket\n");
		recover();
		errors++;
		return 1;
	}
	lex();

	// symbol
	if (ltoken.type != LTYPE_SYMBOL)
	{
		prettyprint("Expected a symbol\n");
		recover();
		errors++;
		return 1;
	}
	setEntry(ltoken.buf);
	lex();

	// )
	if (ltoken.type != LTYPE_CLOSE_PAREN)
	{
		prettyprint("Expected a closing bracket\n");
		recover();
		errors++;
		return 1;
	}
	lex();

	return 1;
}
