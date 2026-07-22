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
		currentSymbol = -1;
		symbolFlags   = 0;
		if (currentSection >= 0)
		{
			struct MiO *section = (void *)&emitbuf[currentSection];

			char *s = ltok.buf;
			while (*s)
			{
				switch (*s)
				{
				case 'x':
					symbolFlags |= MIO_SYMBOL_FLAG_EXECUTABLE;
					break;
				case 'r':
					symbolFlags |= MIO_SYMBOL_FLAG_READABLE;
					break;
				case 'w':
					symbolFlags |= MIO_SYMBOL_FLAG_WRITABLE;
					break;
				case 't':
					symbolFlags |= MIO_SYMBOL_FLAG_THREAD_LOCAL;
					break;
				case 'v':
					section->flags |= MIO_FLAG_VIRTUAL;
					symbolFlags    |= MIO_SYMBOL_FLAG_VIRTUAL;
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
	else // so we don't consume anything twice
	{
		lex();
	}

	return 1;
}
