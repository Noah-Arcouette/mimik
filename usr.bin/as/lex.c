#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <wctype.h>
#include <stdio.h>
#include "main.h"

FILE *lfp;
const char *lfilename;

/**
 * Push a character onto a token, ensuring that the buffer stays null terminated
 * @param c The character
 * @file lex.c
 */
static void
_pushc (wchar_t c)
{
	ltok.size++;
	if ((ltok.size+1) > ltok.bufcp)
	{
		ltok.bufcp = (3*(ltok.size+1))/2;
		void *buf = realloc(ltok.buf, sizeof(wchar_t)*ltok.bufcp);
		if (!buf)
		{
			fprintf(stderr, gettext("%s: Failed to allocate memory\n"), self);
			errors++;
			return;
		}
		ltok.buf = buf;
	}
	ltok.buf[ltok.size-1] = c;
	ltok.buf[ltok.size  ] = L'\0';
}

void
lex (void)
{
_try_again:
	ltok.offset += ltok.size;
	ltok.size    = 0;

	wint_t d;
	wint_t c = fgetwc(lfp);

	switch (c)
	{
	case L' ':
	case L'\t':
		ltok.size++;
		goto _try_again;
	case L'\n':
		ltok.lineno++;
		ltok.offset = 0;
		ltok.type = TOK_NEWLINE;
		break;
	case L':':
	case L';':
	case L'[':
	case L']':
	case L'+':
	case L'-':
		_pushc(c);
		ltok.type = c;
		break;
	case WEOF:
		ltok.type = TOK_EOF;
		break;
	case L'%':
		while (iswalnum(c) || c == L'%')
		{
			_pushc(c);
			c = fgetwc(lfp);
		}
		ungetwc(c, lfp); // unget the non-matching character
		ltok.type = TOK_REGISTER;
		break;
	case L'"':
		d = L'\\';
		while (c != L'"' || d == L'\\')
		{
			d = c;
			_pushc(c);
			c = fgetwc(lfp);
		}
		_pushc(c);
		c = fgetwc(lfp);
		ltok.type = TOK_STRING;
		break;
	default:
		if (iswdigit(c))
		{
			while (iswalnum(c))
			{
				_pushc(c);
				c = fgetwc(lfp);
			}
			ungetwc(c, lfp); // unget the non-matching character
			ltok.type = TOK_NUMBER;
			break;
		}

		if (iswalpha(c) || c == L'.' || c == L'_')
		{
			while (iswalnum(c) || c == L'.' || c == L'_')
			{
				_pushc(c);
				c = fgetwc(lfp);
			}
			ungetwc(c, lfp); // unget the non-matching character

			if (!wcscmp(ltok.buf, L".arch"))
			{
				ltok.type = TOK_ARCH;
				break;
			}
			if (!wcscmp(ltok.buf, L".uarch"))
			{
				ltok.type = TOK_UARCH;
				break;
			}
			if (!wcscmp(ltok.buf, L".archflag"))
			{
				ltok.type = TOK_ARCHFLAG;
				break;
			}
			if (!wcscmp(ltok.buf, L".sys"))
			{
				ltok.type = TOK_SYS;
				break;
			}
			if (!wcscmp(ltok.buf, L".usys"))
			{
				ltok.type = TOK_USYS;
				break;
			}
			if (!wcscmp(ltok.buf, L".sysflag"))
			{
				ltok.type = TOK_SYSFLAG;
				break;
			}
			if (!wcscmp(ltok.buf, L".section"))
			{
				ltok.type = TOK_SECTION;
				break;
			}
			if (!wcscmp(ltok.buf, L".global"))
			{
				ltok.type = TOK_GLOBAL;
				break;
			}
			if (!wcscmp(ltok.buf, L".byte"))
			{
				ltok.type = TOK_BYTE;
				break;
			}
			if (!wcscmp(ltok.buf, L".word"))
			{
				ltok.type = TOK_WORD;
				break;
			}
			if (!wcscmp(ltok.buf, L".res.byte"))
			{
				ltok.type = TOK_RES_BYTE;
				break;
			}
			if (!wcscmp(ltok.buf, L".res.word"))
			{
				ltok.type = TOK_RES_WORD;
				break;
			}

			ltok.type = TOK_SYMBOL;
			break;
		}
		// else

		_pushc(c);
		ltok.type = TOK_UNKNOWN;
		break;
	}
}
