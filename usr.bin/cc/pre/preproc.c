#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

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

	// macro expansion
	if (lex_token.type == LEX_TOKEN_TYPE_SYMBOL)
	{
		void *dat = srch_find(&pre_macro, lex_token.buf);
		if (dat)
		{
			char *macro_name = strdup(lex_token.buf);
			if (!macro_name)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
				return;
			}

			FILE *macro_fp = fmemopen(dat, strlen(dat), "r");
			if (!macro_fp)
			{
				fprintf(stderr,
					gettext("%s: Failed to open memory file for macro, %s\n"),
					self, strerror(errno));
				errors++;
				free(macro_name);
				return;
			}

			struct lex_context lc = {
				.type = LEX_CONTEXT_TYPE_MACRO_EXPAND,
				.name = macro_name,
				.fp   = macro_fp,
				.lineno = 1,
				.offset = 0,
				.size   = 0
			};
			lex_push(&lc);
			preproc();
		}
	}

	if (lex_token.type == LEX_TOKEN_TYPE_NEWLINE) lineIsDirty = 0;
	else if (lex_token.type != LEX_TOKEN_TYPE_WHITESPACE) lineIsDirty = 1;
}
