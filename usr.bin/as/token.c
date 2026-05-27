#include <stdlib.h>
#include "main.h"

void
createToken (struct token *tok)
{
	tok->type = TOK_EOF;

	tok->lineno = 1;
	tok->offset = 0;
	tok->size   = 0;

	tok->bufcp = 0;
	tok->buf   = NULL;
}

void
resetToken (struct token *tok)
{
	tok->type = TOK_EOF;

	tok->lineno = 1;
	tok->offset = 0;
	tok->size   = 0;
}

void
destroyToken (struct token *tok)
{
	free(tok->buf);

	tok->type = TOK_EOF;

	tok->lineno = 0;
	tok->offset = 0;
	tok->size   = 0;

	tok->bufcp = 0;
	tok->buf   = NULL;
}
