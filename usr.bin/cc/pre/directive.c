#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <string.h>

/*
The if logic:


success = 0
depth   = 0
write   = 1

if x:
	if write && depth == success && x:
		write = 1
		success++
	else:
		write = 0
	depth++
elif x:
	if (depth-1) == success && x:
		write = 1
		success++
	else:
		write = 0
endif:
	if depth == success:
		write = 1
		success--
	depth--

*/

void
pre_directive (void)
{
	// # \n (is technically allowed)
	if (lex_token.type == LEX_TOKEN_TYPE_NEWLINE) return;

	if (!strcmp(lex_token.buf, "include"))
	{
		if (pre_if_writing)
		{
			lex_nowhitespace();
			pre_include();
		}
		else
		{
			lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
		}
	}
	else if (!strcmp(lex_token.buf, "ifdef"))
	{
		lex_nowhitespace();
		pre_directiveIfdef(0);
	}
	else if (!strcmp(lex_token.buf, "ifndef"))
	{
		lex_nowhitespace();
		pre_directiveIfdef(1);
	}
	else if (!strcmp(lex_token.buf, "elifdef"))
	{
		lex_nowhitespace();
		pre_directiveElifdef(0);
	}
	else if (!strcmp(lex_token.buf, "elifndef"))
	{
		lex_nowhitespace();
		pre_directiveElifdef(1);
	}
	else if (!strcmp(lex_token.buf, "else"))
	{
		lex_nowhitespace();
		pre_directiveElse();
	}
	else if (!strcmp(lex_token.buf, "endif"))
	{
		lex_nowhitespace();
		pre_directiveEndif();
	}
	else if (!strcmp(lex_token.buf, "define"))
	{
		if (pre_if_writing)
		{
			lex_nowhitespace();
			pre_define();
		}
		else
		{
			lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
		}
	}
	else if (!strcmp(lex_token.buf, "warning"))
	{
		if (pre_if_writing)
		{
			lex_prettyprint("");
		}
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
	else if (!strcmp(lex_token.buf, "error"))
	{
		if (pre_if_writing)
		{
			lex_prettyprint("");
			errors++;
		}
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
	else
	{
		lex_prettyprint(gettext("Unknown directive\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
}
