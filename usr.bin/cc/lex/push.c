#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct lex_context *lex_context = NULL;
int lex_contexts = 0;

void
lex_push (const struct lex_context *lc)
{
	lex_contexts++;
	void *buf = realloc(lex_context, sizeof(struct lex_context)*lex_contexts);
	if (!buf)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		lex_contexts--;
		return;
	}
	lex_context = buf;

	memcpy(&lex_context[lex_contexts-1], lc, sizeof(struct lex_context));
}
