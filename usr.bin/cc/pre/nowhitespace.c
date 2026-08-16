#include "../pre.h"

void
preproc_nowhitespace (void)
{
	do
	{
		preproc();
	} while (lex_token.type == LEX_TOKEN_TYPE_WHITESPACE ||
			lex_token.type == LEX_TOKEN_TYPE_NEWLINE);
}
