#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>

int64_t period = -1;

static int
_val (int64_t *val)
{
	// (
	if (ltoken.type == LTYPE_OPEN_PAREN)
	{
		lex();
		// expr
		if (!parse_expr(val))
		{
			prettyprint(gettext("Expected an expression after `(`\n"));
			errors++;
			return 1;
		}

		// )
		if (ltoken.type != LTYPE_CLOSE_PAREN)
		{
			prettyprint(gettext("Expected a `)` after the expression\n"));
			errors++;
			return 1;
		}
		lex();
		return 1;
	}

	if (ltoken.type == LTYPE_INTEGER)
	{
		int64_t a = 0;
		wchar_t *s   = ltoken.buf;
		int negative = 0;
		if (*s == L'+') s++;
		if (*s == L'-')
		{
			s++;
			negative = 1;
		}

		if (*s == L'0')
		{
			s++;
			// hex
			if (*s == L'X' || *s == L'x')
			{
				s++;
				while (*s)
				{
					a *= 16;
					if (*s >= L'0' && *s <= L'9')
					{
						a += *s-'0';
					}
					else if (*s >= L'a' && *s <= L'f')
					{
						a += *s-'a'+10;
					}
					else if (*s >= L'A' && *s <= L'F')
					{
						a += *s-L'A'+10;
					}
					else
					{
						prettyprint(gettext(
							"Hex integer contains non-hex character\n"));
						errors++;
						break;
					}
					s++;
				}
			}
			// octal
			else
			{
				while (*s)
				{
					a *= 8;
					if (*s >= L'0' && *s <= L'7')
					{
						a += *s-L'0';
					}
					else
					{
						prettyprint(gettext(
							"Octal integer contains non-octal character\n"));
						errors++;
						break;
					}
					s++;
				}
			}
		}
		// decimal
		else
		{
			while (*s)
			{
				a *= 10;
				if (*s >= L'0' && *s <= L'9')
				{
					a += *s-L'0';
				}
				else
				{
					prettyprint(gettext(
						"Decimal integer contains non-decimal character\n"));
					errors++;
					break;
				}
				s++;
			}
		}

		lex();
		if (negative) a = -a;
		if (val) *val = a;
		return 1;
	}

	if (ltoken.type == LTYPE_SYMBOL)
	{
		// period
		if (!wcscmp(ltoken.buf, L"."))
		{
			lex();
			if (period >= 0)
			{
				if (val) *val = period;
				return 1;
			}
			prettyprint(gettext(
				"Period is not an absolute value at the moment\n"));
			errors++;
			return 1;
		}

		// find the symbol
		struct MiO_Symbol *sym = findSymbol(ltoken.buf);
		if (!sym)
		{
			prettyprint(gettext("Symbol `%S' does not exist\n"), ltoken.buf);
			errors++;
			if (val) *val = 0;
			lex();
			return 1;
		}

		// make sure its a literal
		if (le16toh(sym->flags) & MIO_SYMBOL_FLAG_LITERAL)
		{
			if (val) *val = le64toh(sym->value);
			lex();
			return 1;
		}
		prettyprint(gettext("Symbol `%S' is not a literal\n"), ltoken.buf);
		errors++;
		if (val) *val = 0;
		lex();
		return 1;
	}

	return 0;
}

static int
_mul (int64_t *val)
{
	int64_t a;
	if (!_val(&a))
	{
		return 0;
	}

	// * or /
	int op; // 1 (star), 2 (slash)
	if (ltoken.type == LTYPE_MULTIPLY)
	{
		op = 1;
	}
	else if (ltoken.type == LTYPE_DIVIDE)
	{
		op = 2;
	}
	else
	{
		if (val) *val = a;
		return 1;
	}
	lex();

	// b
	int64_t b;
	if (!_val(&b))
	{
		if (val) *val = a;
		prettyprint(gettext(
			"Missing other side of multiplication or division\n"));
		errors++;
		return 1;
	}

	// do the math
	if (op == 1)
	{
		a *= b;
	}
	else
	{
		a /= b;
	}
	if (val) *val = a;
	return 1;
}

int
parse_expr (int64_t *val)
{
	int64_t a;
	if (!_mul(&a))
	{
		return 0;
	}

	// + or -
	int op; // 1 (plus), 2 (sub)
	if (ltoken.type == LTYPE_PLUS)
	{
		op = 1;
	}
	else if (ltoken.type == LTYPE_SUBTRACT)
	{
		op = 2;
	}
	else
	{
		if (val) *val = a;
		return 1;
	}
	lex();

	// b
	int64_t b;
	if (!_mul(&b))
	{
		if (val) *val = a;
		prettyprint(gettext("Missing other side of addition or subtraction\n"));
		errors++;
		return 1;
	}

	// do the math
	if (op == 1)
	{
		a += b;
	}
	else
	{
		a -= b;
	}
	if (val) *val = a;
	return 1;
}
