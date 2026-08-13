#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void
pre_include (void)
{
	int searchLocal;

	// < ... >
	if (lex_token.type == LEX_TOKEN_TYPE_LESSER)
	{
		searchLocal = 0;
		while (1)
		{
			int c = lex_getc();

			if (c == EOF ||
				c == '\n')
			{
				lex_prettyprint(gettext("Missing closing angle bracket\n"));
				errors++;
			}

			if (c == '>') break;
		}
	}
	// " ... "
	else if (lex_token.type == LEX_TOKEN_TYPE_STRING)
	{
		searchLocal = 1;
	}
	else
	{
		lex_prettyprint(
			gettext("Expected a string or opening angle bracket\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
		return;
	}

	// strip the enclosing
	char *s = lex_token.buf+1;
	s[lex_token.bufsz-2] = '\0';

	char *path = pre_findInclude(s, searchLocal);
	if (!path)
	{
		lex_prettyprint(gettext("Failed to find include\n"));
		errors++;
	}

	lex_nowhitespace(); // eat the path

	// check for garbage
	if (lex_token.type != LEX_TOKEN_TYPE_NEWLINE)
	{
		lex_prettyprint(gettext("Loose tokens after include path\n"));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
	}

	if (path)
	{
		// push the lexer context if we can
		FILE *fp = fopen(path, "r");
		if (!fp)
		{
			lex_prettyprint(gettext("Failed to open include path `%s', %s\n"),
				path, strerror(errno));
			free(path);
			errors++;
		}

		// push the context
		struct lex_context lc = {
			.type = LEX_CONTEXT_TYPE_INCLUDED_FILE,
			.fp   = fp,
			.name = path,
			.lineno = 1,
			.offset = 0,
			.size   = 0,
		};
		lex_push(&lc);
	}
}
