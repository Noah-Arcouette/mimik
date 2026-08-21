#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <errno.h>

struct ltoken ltoken = {
	.type   = LTYPE_EOF,
	.lineno = 1,
	.offset = 0,
	.length = 0,
	.bufcp  = 0,
	.buf    = NULL
};

FILE       *lfp       = NULL;
const char *lfilename = NULL;

int lex_symbolCanGlob = 0;

static wint_t
_getc (void)
{
	wint_t c = fgetwc(lfp);
	if (c == WEOF)
	{
		if (ferror(lfp))
		{
			fprintf(stderr,
				gettext("%s: Failed to read from script file, %s\n"),
				self, strerror(errno));
			errors++;
		}
		return EOF;
	}

	// grow buffer
	ltoken.length++;
	if ((ltoken.length+1) > ltoken.bufcp)
	{
		ltoken.bufcp = 3*(ltoken.length+1)/2;
		void *buf = realloc(ltoken.buf, ltoken.bufcp*sizeof(wchar_t));
		if (!buf)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			return EOF;
		}
		ltoken.buf = buf;
	}
	// add the character and null
	ltoken.buf[ltoken.length-1] = c;
	ltoken.buf[ltoken.length  ] = L'\0';
	return c;
}

static void
_ungetc (wint_t c)
{
	if (ltoken.length == 0)
	{
		return;
	}

	ltoken.length--;
	ltoken.buf[ltoken.length] = L'\0';
	ungetwc(c, lfp);
}

void
lex (void)
{
_lex:
	ltoken.offset += ltoken.length;
	ltoken.length = 0;

	wint_t c = _getc();

	switch (c)
	{
	// eat white space
	case L' ':
	case L'\t':
		goto _lex;
	case L'\n': // manage new lines
		ltoken.lineno++;
		ltoken.length = 0;
		ltoken.offset = 0;
		goto _lex;
	case L'{':
	case L'}':
	case L'=':
	case L';':
	case L':':
	case L'(':
	case L')':
	case L'+':
	case L'-':
		ltoken.type = c;
		break;
	case WEOF:
		ltoken.type = LTYPE_EOF;
		break;
	default:
		// non-glob
		if ((c == L'/' || c == L'*') && !lex_symbolCanGlob)
		{
			ltoken.type = c;
			break;
		}

		if (iswalpha(c) || c == L'_' || c == L'.' || c == L'*' || c == L'/')
		{
			while (iswalnum(c) || c == L'_' || c == L'.' || (
				(c == L'*' || c == L'/') &&
				lex_symbolCanGlob
			))
			{
				c = _getc();
			}
			_ungetc(c);
			ltoken.type = LTYPE_SYMBOL;

			// check for special symbols
			switch (ltoken.buf[0])
			{
			case L'Q':
				if (!wcscmp(ltoken.buf+1, L"UAD"))
				{
					ltoken.type = LTYPE_QUAD;
				}
				break;
			case L'L':
				if (!wcscmp(ltoken.buf+1, L"ONG"))
				{
					ltoken.type = LTYPE_LONG;
				}
				break;
			case L'E':
				if (!wcscmp(ltoken.buf+1, L"NTRY"))
				{
					ltoken.type = LTYPE_ENTRY;
				}
				break;
			case L'A':
				if (!wcscmp(ltoken.buf+1, L"RCH"))
				{
					ltoken.type = LTYPE_ARCH;
				}
				else if (!wcscmp(ltoken.buf+1, L"RCHFLAG"))
				{
					ltoken.type = LTYPE_ARCHFLAG;
				}
				else if (!wcscmp(ltoken.buf+1, L"LIGN"))
				{
					ltoken.type = LTYPE_ALIGN;
				}
				break;
			case L'U':
				if (!wcscmp(ltoken.buf+1, L"ARCH"))
				{
					ltoken.type = LTYPE_UARCH;
				}
				else if (!wcscmp(ltoken.buf+1, L"SYS"))
				{
					ltoken.type = LTYPE_USYS;
				}
				break;
			case L'S':
				if (!wcscmp(ltoken.buf+1, L"YS"))
				{
					ltoken.type = LTYPE_SYS;
				}
				else if (!wcscmp(ltoken.buf+1, L"YSFLAG"))
				{
					ltoken.type = LTYPE_SYSFLAG;
				}
				else if (!wcscmp(ltoken.buf+1, L"ECTIONS"))
				{
					ltoken.type = LTYPE_SECTIONS;
				}
				else if (!wcscmp(ltoken.buf+1, L"HORT"))
				{
					ltoken.type = LTYPE_SHORT;
				}
				break;
			case L'B':
				if (!wcscmp(ltoken.buf+1, L"YTE"))
				{
					ltoken.type = LTYPE_BYTE;
				}
				break;
			case L'N':
				if (!wcscmp(ltoken.buf+1, L"OLOAD"))
				{
					ltoken.type = LTYPE_NOLOAD;
				}
				break;
			}

			break;
		}

		if (iswdigit(c))
		{
			while (iswalnum(c))
			{
				c = _getc();
			}
			_ungetc(c);
			ltoken.type = LTYPE_INTEGER;
			break;
		}

		ltoken.type = LTYPE_UNKNOWN;
		break;
	}
}
