#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>

int
parse_sections (void)
{
	if (ltoken.type != LTYPE_SECTIONS) return 0;
	lex();

	// {
	if (ltoken.type != LTYPE_OPEN_CURLY)
	{
		prettyprint(gettext("Expected opening curly bracket\n"));
		errors++;
		recover();
		return 1;
	}
	lex();

	// until } or EOF
	while (ltoken.type != LTYPE_CLOSE_CURLY && ltoken.type != LTYPE_EOF)
	{
		// symbol
		if (ltoken.type != LTYPE_SYMBOL)
		{
			prettyprint(gettext("Expected a symbol\n"));
			errors++;
			recover();
			continue;
		}
		char *sym = strdup(ltoken.buf);
		if (!sym)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			recover();
			continue;
		}
		lex();

		// create new symbol
		// =
		if (ltoken.type == LTYPE_EQUAL)
		{
			lex();

			// expr
			int64_t val;
			if (!parse_expr(&val))
			{
				prettyprint(gettext("Expected an expression\n"));
				errors++;
				recover();
				free(sym);
				continue;
			}
			// newSymbol(val, 0, LITERAL, sym);
			free(sym);

			// ;
			if (ltoken.type != LTYPE_SEMICOLON)
			{
				prettyprint(gettext("Expected a semicolon"));
				errors++;
				recover();
				continue;
			}
			lex();
			continue;
		}

		// [expr] [(noload)] : [expr] { file(section...)... }
		// create new section

		prettyprint(gettext(
			"Expected an assignment, expression, (NOLOAD), or a colon\n"));
		errors++;
		recover();
		free(sym);
	}
	lex();

	return 1;
}
