#include "../lex.h"
#include <ctype.h>

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
	case '\n':
		lex_token.type = LEX_TOKEN_TYPE_NEWLINE;
		break;
	case EOF:
		lex_token.type = LEX_TOKEN_TYPE_EOF;
		break;
	default:
		if (isspace(c))
		{
			while (isspace(c))
			{
				c = lex_getc();
			}
			lex_ungetc(c);
			lex_token.type = LEX_TOKEN_TYPE_WHITESPACE;
			break;
		}

		lex_token.type = LEX_TOKEN_TYPE_UNKNOWN;
		break;
	}
}
