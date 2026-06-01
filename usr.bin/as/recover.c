#include "main.h"

void
recover (void)
{
	do
	{
		lex();
	} while (ltok.type != TOK_EOF &&
			 ltok.type != TOK_NEWLINE);
}
