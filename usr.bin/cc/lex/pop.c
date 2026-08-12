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
}
