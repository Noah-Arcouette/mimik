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
	case '~':
		lex_token.type = LEX_TOKEN_TYPE_BITWISE_NOT;
		break;
	case '#':
		lex_token.type = LEX_TOKEN_TYPE_HASH;
		break;
	case '(':
		lex_token.type = LEX_TOKEN_TYPE_OPEN_PAREN;
		break;
	case ')':
		lex_token.type = LEX_TOKEN_TYPE_CLOSE_PAREN;
		break;
	case '[':
		lex_token.type = LEX_TOKEN_TYPE_OPEN_SQUARE;
		break;
	case ']':
		lex_token.type = LEX_TOKEN_TYPE_CLOSE_SQUARE;
		break;
	case '{':
		lex_token.type = LEX_TOKEN_TYPE_OPEN_CURLY;
		break;
	case '}':
		lex_token.type = LEX_TOKEN_TYPE_CLOSE_CURLY;
		break;
	case ';':
		lex_token.type = LEX_TOKEN_TYPE_SEMICOLON;
		break;
	case ':':
		lex_token.type = LEX_TOKEN_TYPE_COLON;
		break;
	case ',':
		lex_token.type = LEX_TOKEN_TYPE_COMMA;
		break;
	case '?':
		lex_token.type = LEX_TOKEN_TYPE_TERTIARY;
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
