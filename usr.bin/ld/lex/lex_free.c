#include "../lex.h"
#include <stdlib.h>

void
lex_free (void)
{
	ltoken.type   = LTYPE_EOF;
	ltoken.lineno = 0;
	ltoken.offset = 0;
	ltoken.length = 0;
	ltoken.bufcp  = 0;

	free(ltoken.buf);
	ltoken.buf = NULL;

	if (lfp)
	{
		fclose(lfp);
		lfp = NULL;
	}
}
