#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>

int
parse_sys (void)
{
	if (ltoken.type != LTYPE_SYS) return 0;
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

	switch (ltoken.buf[0])
	{
	case 'u':
		// undefined
		if (!strcmp(ltoken.buf+1, "ndefined"))
		{
			outputArch.sys      = htole16(MIO_ARCH_SYS_UNDEFINED);
			outputArch.usys     = 0;
			outputArch.sysflags = 0;
			break;
		}
		goto _unknown;
	default:
	_unknown:
		prettyprint(gettext("Unknown system type\n"));
		errors++;
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
