#include <libintl.h>
#include "parse.h"
#include "main.h"

void
parse (void)
{
	lex();
	do
	{
		// sections
		if (parse_section()) continue;

		// architecture
		if (parse_architecture()) continue;

		// symbols
		// gaps
		// emit data
		// reserve data
		// x86-16

		// ignore newline
		if (ltok.type == TOK_NEWLINE)
		{
			lex();
			continue;
		}

		// loose token
		prettyprint(gettext("Uncaught token\n"));
		errors++;
		recover();
	} while (ltok.type != TOK_EOF);
}
