#include <stdlib.h>
#include "main.h"

struct token ltok = {
	.type = TOK_EOF,

	.lineno = 1,
	.offset = 0,
	.size   = 0,

	.bufcp = 0,
	.buf   = NULL
};

void
resetToken (void)
{
	ltok.type = TOK_EOF;

	ltok.lineno = 1;
	ltok.offset = 0;
	ltok.size   = 0;
}

void
destroyToken (void)
{
	free(ltok.buf);

	ltok.type = TOK_EOF;

	ltok.lineno = 0;
	ltok.offset = 0;
	ltok.size   = 0;

	ltok.bufcp = 0;
	ltok.buf   = NULL;
}
