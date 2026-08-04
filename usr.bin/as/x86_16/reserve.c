#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <libintl.h>

int
parse_x86_16_reserve (void)
{
	// .res.word
	if (ltok.type == TOK_RES_WORD)
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

		reserve(amt*2);
		return 1;
	}

	return 0;
}
