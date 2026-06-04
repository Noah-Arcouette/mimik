#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <libintl.h>

int
parse_section (void)
{
	// .section
	if (ltok.type != TOK_SECTION) return 0;
	lex();

	// name
	if (ltok.type != TOK_SYMBOL)
	{
		prettyprint(gettext("Expected a token\n"));
		errors++;
		recover();
		return 1;
	}
	emitSection(ltok.buf);
	lex();

	// flags (optional)
	if (ltok.type == TOK_SYMBOL)
	{
		if (currentSection >= 0)
		{
			struct MiO *section = (void *)&emitbuf[currentSection];

			char *s = ltok.buf;
			while (*s)
			{
				switch (*s)
				{
				case 'x':
				case 'r':
				case 'w':
					prettyprint(gettext(
						"Section flag `%c' is current not implemented\n"), *s);
					errors++;
					break;
				case 'v':
					section->flags |= MIO_FLAG_VIRTUAL;
					break;
				case '-':
				case '\0':
					break;
				}
				s++;
			}
		}

		lex();
	}

	// newline
	if (ltok.type != TOK_NEWLINE)
	{
		prettyprint(gettext("Expected a newline\n"));
		recover();
		errors++;
	}
	lex();

	return 1;
}
