#include "../lex.h"

void
recover (void)
{
	long lineno = ltoken.lineno;
	while (1)
	{
		lex();
		if (lineno != ltoken.lineno) break;
		if (ltoken.type == LTYPE_EOF) break;
	}
}
