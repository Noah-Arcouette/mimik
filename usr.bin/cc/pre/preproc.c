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

	static int lineIsDirty = 0;

	// directives
	if (!lineIsDirty && lex_token.type == LEX_TOKEN_TYPE_HASH)
	{
		lex_nowhitespace();
		pre_directive();
	}

	if (lex_token.type == LEX_TOKEN_TYPE_NEWLINE) lineIsDirty = 0;
	else if (lex_token.type != LEX_TOKEN_TYPE_WHITESPACE) lineIsDirty = 1;
}
