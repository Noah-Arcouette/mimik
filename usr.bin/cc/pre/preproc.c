#include "../pre.h"

void
preproc (void)
{
	// newline catch ups
	static int newlineCatchup = 0;
	if (newlineCatchup)
	{
		newlineCatchup--;
		lex_ungetc('\n');
		lex();
		return;
	}

	lex();

	// comments
	if (lex_token.type == LEX_TOKEN_TYPE_COMMENT)
	{
		for (int i = 0; i<lex_token.bufsz; i++)
		{
			if (lex_token.buf[i] == '\n') newlineCatchup++;
		}
		preproc();
	}
}
