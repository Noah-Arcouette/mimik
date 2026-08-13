#include "../lex.h"

void
lex_nowhitespace (void)
{
	do
	{
		lex();
	} while (lex_token.type == LEX_TOKEN_TYPE_WHITESPACE);
}
