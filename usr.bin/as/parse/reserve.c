#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <libintl.h>

int
parse_reserve (void)
{
	// .res.byte
	if (ltok.type == TOK_RES_BYTE)
	{
		lex();

		long amt;
		if (!parse_number(&amt))
		{
			prettyprint(gettext("Expected a number\n"));
			errors++;
			recover();
			return 1;
		}

		reserve(amt);
		return 1;
	}

	// .res.word
	if (ltok.type == TOK_RES_WORD)
	{
		prettyprint(gettext("Architecture word size unknown\n"));
		errors++;
		recover();
		return 1;
	}

	return 0;
}
