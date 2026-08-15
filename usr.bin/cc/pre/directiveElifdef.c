#include "../main.h"
#include "../pre.h"
#include <libintl.h>

void
pre_directiveElifdef (int negate)
{
	int x;
	// symbol
	if (lex_token.type != LEX_TOKEN_TYPE_SYMBOL)
	{
		lex_prettyprint(gettext("Expected a symbol\n"));
		errors++;
		x = 0;
	}
	else if (srch_find(&pre_macro, lex_token.buf))
	{
		x = !negate;
	}
	else
	{
		x = negate;
	}
	lex_nowhitespace();

	// newline
	if (lex_token.type != LEX_TOKEN_TYPE_NEWLINE)
	{
		lex_prettyprint(gettext("Expected a newline\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}

	if (!pre_if_depth)
	{
		lex_prettyprint(gettext("elif without an if\n"));
		errors++;
		return;
	}

	// the if logic
	if ((pre_if_depth-1) == pre_if_success && x)
	{
		pre_if_writing = 1;
		pre_if_success++;
	}
	else
	{
		pre_if_writing = 0;
	}
}
