#include "../lex.h"

void
lex_newToken (void)
{
	if (!lex_contexts) return;

	struct lex_context *lc = &lex_context[lex_contexts-1];

	lc->offset += lc->size;
	lc->size = 0;
	lex_token.bufsz = 0;
}
