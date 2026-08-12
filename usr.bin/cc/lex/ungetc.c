#include "../lex.h"

void
lex_ungetc (char c)
{
	if (!lex_contexts) return;
	if (c == EOF) return;

	struct lex_context *lc = &lex_context[lex_contexts-1];
	ungetc(c, lc->fp);

	if (c == '\n') lc->lineno--;
	else
	{
		lex_token.bufsz--;
		lex_token.buf[lex_token.bufsz] = '\0';

		if (lc->size) lc->size--;
	}
}
