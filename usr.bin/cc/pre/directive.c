#include "../main.h"
#include "../pre.h"

void
pre_directive (void)
{
	// # \n (is technically allowed)
	if (lex_token.type == LEX_TOKEN_TYPE_NEWLINE) return;

	// if (!strcmp(lex_token.buf, "include"))
	// {
	// 	pre_include();
	// }
	// else
	{
		lex_prettyprint("Unknown directive\n");
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}
}
