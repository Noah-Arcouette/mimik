#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <string.h>

void
pre_directive (void)
{
	// # \n (is technically allowed)
	if (lex_token.type == LEX_TOKEN_TYPE_NEWLINE) return;

	if (!strcmp(lex_token.buf, "include"))
	{
		lex_nowhitespace();
		pre_include();
	}
	if (!strcmp(lex_token.buf, "define"))
	{
		lex_nowhitespace();
		pre_define();
	}
	else
	{
		lex_prettyprint(gettext("Unknown directive\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
}
