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
	else if (!strcmp(lex_token.buf, "define"))
	{
		lex_nowhitespace();
		pre_define();
	}
	else if (!strcmp(lex_token.buf, "warning"))
	{
		lex_prettyprint("");
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
	else if (!strcmp(lex_token.buf, "error"))
	{
		lex_prettyprint("");
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
		errors++;
	}
	else
	{
		lex_prettyprint(gettext("Unknown directive\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
}
