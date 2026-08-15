#include "../main.h"
#include "../pre.h"
#include <libintl.h>

int pre_if_writing = 1;
int pre_if_depth   = 0;
int pre_if_success = 0;

void
pre_directiveIfdef (int negate)
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

	// the if logic
	if (pre_if_writing && pre_if_depth == pre_if_success && x)
	{
		pre_if_writing = 1;
		pre_if_success++;
	}
	else
	{
		pre_if_writing = 0;
	}
	pre_if_depth++;
}
