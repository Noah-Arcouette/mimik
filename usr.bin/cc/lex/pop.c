#include "../lex.h"
#include <stdlib.h>
#include <stdio.h>

void
lex_pop (void)
{
	if (!lex_contexts) return; // no underflow

	lex_contexts--;
	struct lex_context *lc = &lex_context[lex_contexts];
	fclose(lc->fp); // close the file
	switch (lc->type)
	{
	case LEX_CONTEXT_TYPE_MACRO_EXPAND:
		if (lex_lineMarkers)
		{
			fprintf(lex_lineMarkers, "\n");
		}
	case LEX_CONTEXT_TYPE_INCLUDED_FILE:
		free(lc->name);
		break;
	case LEX_CONTEXT_TYPE_NORMAL_FILE:
		break;
	}

	if (!lex_contexts)
	{
		free(lex_context); // so we don't have a final memory leak
		lex_context = NULL;
	}
	// though more memory is used if we don't resize it
	// successive pushes should be faster (making this a weird vectored array)
	// else
	// {
	// 	lex_context =
	// 		realloc(lex_context, sizeof(struct lex_context)*lex_contexts);
	// }

	if (lex_lineMarkers)
	{
		if (lex_contexts > 0)
		{
			// last context
			lc = &lex_context[lex_contexts-1];
			fprintf(lex_lineMarkers, "# %d \"%s\"\n", lc->lineno-1, lc->name);
		}
	}
}
