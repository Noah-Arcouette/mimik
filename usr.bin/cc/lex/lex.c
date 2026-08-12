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
	lex_pop();
}
