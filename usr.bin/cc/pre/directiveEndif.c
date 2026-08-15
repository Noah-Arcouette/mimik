#include "../main.h"
#include "../pre.h"
#include <libintl.h>

void
pre_directiveEndif (void)
{
	// newline
	if (lex_token.type != LEX_TOKEN_TYPE_NEWLINE)
	{
		lex_prettyprint(gettext("Expected a newline\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}

	if (!pre_if_depth)
	{
		lex_prettyprint(gettext("endif without an if\n"));
		errors++;
		return;
	}

	pre_if_depth--;
	if (pre_if_depth < pre_if_success)
	{
		pre_if_success--;
	}
	if (pre_if_depth == pre_if_success)
	{
		pre_if_writing = 1;
	}
}
