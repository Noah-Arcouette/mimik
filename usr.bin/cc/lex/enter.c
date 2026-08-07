#include "../lex.h"

struct lex_token lex_token = {
	.type  = LEX_TOKEN_TYPE_EOF,
	.buf   = NULL,
	.bufcp = 0,
	.bufsz = 0
};

struct lex_context lex_context = {
	.fp     = NULL,
	.path   = NULL,
	.lineno = 0,
	.offset = 0,
	.size   = 0
};

void
lex_enter (const char *path, FILE *fp)
{
	lex_context.fp     = fp;
	lex_context.path   = path;
	lex_context.lineno = 1;
	lex_context.offset = 0;
	lex_context.size   = 0;

	lex_token.type  = LEX_TOKEN_TYPE_EOF;
	lex_token.bufsz = 0;
}
