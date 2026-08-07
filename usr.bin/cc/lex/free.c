#include "../lex.h"
#include <stdlib.h>

void
lex_free (void)
{
	lex_context.fp     = NULL;
	lex_context.path   = NULL;
	lex_context.lineno = 1;
	lex_context.offset = 0;
	lex_context.size   = 0;

	free(lex_token.buf);
	lex_token.type  = LEX_TOKEN_TYPE_EOF;
	lex_token.bufsz = 0;
	lex_token.bufcp = 0;
	lex_token.buf   = NULL;
}
