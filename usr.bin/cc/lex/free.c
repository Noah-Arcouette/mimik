#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <stdlib.h>
#include <stdio.h>

void
lex_free (void)
{
	for (int i = 0; i<lex_contexts; i++)
	{
		switch (lex_context[i].type)
		{
		case LEX_CONTEXT_TYPE_NORMAL_FILE:
		case LEX_CONTEXT_TYPE_INCLUDED_FILE:
			fprintf(stderr,
				gettext("%s: File `%s' is still open\n"),
				self, lex_context[i].name);
			errors++;
			break;
		}
		fclose(lex_context[i].fp);
	}
	free(lex_context);
	lex_context  = NULL;
	lex_contexts = 0;

	// the token
	free(lex_token.buf);
	lex_token.buf   = NULL;
	lex_token.bufsz = 0;
	lex_token.bufcp = 0;
}
