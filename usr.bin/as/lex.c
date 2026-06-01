#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"

FILE *lfp;
const char *lfilename;

/**
 * Push a character onto a token, ensuring that the buffer stays null terminated
 * @param c The character
 * @file lex.c
 */
static void
_pushc (char c)
{
	ltok.size++;
	if ((ltok.size+1) > ltok.bufcp)
	{
		ltok.bufcp = (3*(ltok.size+1))/2;
		void *buf = realloc(ltok.buf, ltok.bufcp);
		if (!buf)
		{
			fprintf(stderr, gettext("%s: Failed to allocate memory\n"), self);
			errors++;
			return;
		}
		ltok.buf = buf;
	}
	ltok.buf[ltok.size-1] = c;
	ltok.buf[ltok.size  ] = '\0';
}

void
lex (void)
{
_try_again:
	ltok.offset += ltok.size;
	ltok.size    = 0;

	int c = fgetc(lfp);

	switch (c)
	{
	case ' ':
	case '\t':
		ltok.size++;
		goto _try_again;
	case '\n':
		ltok.lineno++;
		ltok.offset = 0;
		ltok.type = TOK_NEWLINE;
		break;
	case ':':
		_pushc(c);
		ltok.type = TOK_COLON;
		break;
	case EOF:
		ltok.type = TOK_EOF;
		break;
	default:
		if (isalpha(c) || c == '.' || c == '_')
		{
			while (isalnum(c) || c == '.' || c == '_')
			{
				_pushc(c);
				c = fgetc(lfp);
			}
			ungetc(c, lfp); // unget the non-matching character

			if (!strcmp(ltok.buf, ".arch"))
			{
				ltok.type = TOK_ARCH;
				break;
			}
			if (!strcmp(ltok.buf, ".uarch"))
			{
				ltok.type = TOK_UARCH;
				break;
			}
			if (!strcmp(ltok.buf, ".archflag"))
			{
				ltok.type = TOK_ARCHFLAG;
				break;
			}
			if (!strcmp(ltok.buf, ".sys"))
			{
				ltok.type = TOK_SYS;
				break;
			}
			if (!strcmp(ltok.buf, ".usys"))
			{
				ltok.type = TOK_USYS;
				break;
			}
			if (!strcmp(ltok.buf, ".sysflag"))
			{
				ltok.type = TOK_SYSFLAG;
				break;
			}
			if (!strcmp(ltok.buf, ".section"))
			{
				ltok.type = TOK_SECTION;
				break;
			}
			if (!strcmp(ltok.buf, ".global"))
			{
				ltok.type = TOK_GLOBAL;
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
