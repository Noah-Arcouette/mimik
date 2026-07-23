#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>

int
parse_sysflag (void)
{
	if (ltoken.type != LTYPE_SYSFLAG) return 0;
	lex();

	// (
	if (ltoken.type != LTYPE_OPEN_PAREN)
	{
		prettyprint(gettext("Expected an opening bracket\n"));
		recover();
		errors++;
		return 1;
	}
	lex();

	// symbol
	if (ltoken.type != LTYPE_SYMBOL)
	{
		prettyprint(gettext("Expected a symbol\n"));
		recover();
		errors++;
		return 1;
	}

	switch (le16toh(outputArch.sys))
	{
	case MIO_ARCH_SYS_UNDEFINED:
		prettyprint(gettext(
			"No system flags are available for an undefined major\n"));
		break;
	default:
		prettyprint(gettext("Unknown system is set\n"));
		break;
	}

	lex();

	// )
	if (ltoken.type != LTYPE_CLOSE_PAREN)
	{
		prettyprint(gettext("Expected a closing bracket\n"));
		recover();
		errors++;
		return 1;
	}
	lex();

	return 1;
}
