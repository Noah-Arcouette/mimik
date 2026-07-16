#include "../lex.h"

struct ltoken ltoken = {
	.type   = LTYPE_EOF,
	.lineno = 1,
	.offset = 0,
	.length = 0,
	.bufcp  = 0,
	.buf    = NULL
};

FILE       *lfp       = NULL;
const char *lfilename = NULL;

void
lex (void)
{

}
