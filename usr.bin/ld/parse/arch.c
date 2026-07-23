#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>

int
parse_arch (void)
{
	if (ltoken.type != LTYPE_ARCH) return 0;
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
			outputArch.arch      = htole16(MIO_ARCH_ARCH_UNDEFINED);
			outputArch.uarch     = 0;
			outputArch.archflags = 0;
			break;
		}
		goto _unknown;
	case 'x':
		// x86 16
		if (!strcmp(ltoken.buf+1, "86_16"))
		{
			outputArch.arch      = htole16(MIO_ARCH_ARCH_X86_16);
			outputArch.uarch     = htole16(MIO_ARCH_ARCH_X86_UARCH_I8086);
			outputArch.archflags = 0;
			break;
		}
		goto _unknown;
	default:
	_unknown:
		prettyprint(gettext("Unknown architecture type\n"));
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
