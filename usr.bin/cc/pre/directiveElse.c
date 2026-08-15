#include "../main.h"
#include "../pre.h"
#include <libintl.h>

void
pre_directiveElse (void)
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
		lex_prettyprint(gettext("else without an if\n"));
		errors++;
		return;
	}

	// the if logic
	if ((pre_if_depth-1) == pre_if_success)
	{
		pre_if_writing = 1;
		pre_if_success++;
	}
	else
	{
		pre_if_writing = 0;
	}
}
