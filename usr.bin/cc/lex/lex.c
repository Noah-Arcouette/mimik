#include "../lex.h"

struct lex_token lex_token = {
	.type  = LEX_TOKEN_TYPE_EOF,
	.buf   = NULL,
	.bufsz = 0,
	.bufcp = 0
};

void
lex (void)
{
	// reset the lexer context
	lex_newToken();

	// what is the character
	int c = lex_getc();
	switch (c)
	{
	case EOF:
		lex_token.type = LEX_TOKEN_TYPE_EOF;
		break;
	default:
		lex_token.type = LEX_TOKEN_TYPE_UNKNOWN;
		break;
	}
}
