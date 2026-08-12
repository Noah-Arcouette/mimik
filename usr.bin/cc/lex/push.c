#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct lex_context *lex_context = NULL;
int lex_contexts = 0;

FILE *lex_lineMarkers = NULL;

void
lex_push (const struct lex_context *lc)
{
	lex_contexts++;
	void *buf = realloc(lex_context, sizeof(struct lex_context)*lex_contexts);
	if (!buf)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		lex_contexts--;
		errors++;
		return;
	}
	lex_context = buf;

	memcpy(&lex_context[lex_contexts-1], lc, sizeof(struct lex_context));

	if (lex_lineMarkers)
	{
		if (lex_contexts == 1)
		{
			fprintf(lex_lineMarkers, "# 0 \"%s\"\n", lc->name);
		}
		else if (lex_contexts > 1)
		{
			// last context
			lc = &lex_context[lex_contexts-2];
			fprintf(lex_lineMarkers, "# %d \"%s\"\n", lc->lineno, lc->name);
		}
	}
}
