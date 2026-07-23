#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

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

static int
_getc (void)
{
	int c = fgetc(lfp);
	if (c == EOF)
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
		void *buf = realloc(ltoken.buf, ltoken.bufcp);
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
	ltoken.buf[ltoken.length  ] = '\0';
	return c;
}

static void
_ungetc (int c)
{
	if (ltoken.length == 0)
	{
		return;
	}

	ltoken.length--;
	ltoken.buf[ltoken.length] = '\0';
	ungetc(c, lfp);
}

void
lex (void)
{
_lex:
	ltoken.offset += ltoken.length;
	ltoken.length = 0;

	int c = _getc();

	switch (c)
	{
	// eat white space
	case ' ':
	case '\t':
		goto _lex;
	case '\n': // manage new lines
		ltoken.lineno++;
		ltoken.length = 0;
		ltoken.offset = 0;
		goto _lex;
	case '{':
	case '}':
	case '=':
	case ';':
	case ':':
	case '(':
	case ')':
	case '+':
	case '-':
	case '/':
	case '*':
		ltoken.type = c;
		break;
	case EOF:
		ltoken.type = LTYPE_EOF;
		break;
	default:
		if (isalpha(c) || c == '_' || c == '.')
		{
			while (isalnum(c) || c == '_' || c == '.')
			{
				c = _getc();
			}
			_ungetc(c);
			ltoken.type = LTYPE_SYMBOL;

			// check for special symbols
			switch (ltoken.buf[0])
			{
			case 'E':
				if (!strcmp(ltoken.buf+1, "NTRY"))
				{
					ltoken.type = LTYPE_ENTRY;
				}
				break;
			case 'A':
				if (!strcmp(ltoken.buf+1, "RCH"))
				{
					ltoken.type = LTYPE_ARCH;
				}
				else if (!strcmp(ltoken.buf+1, "RCHFLAG"))
				{
					ltoken.type = LTYPE_ARCHFLAG;
				}
				break;
			case 'U':
				if (!strcmp(ltoken.buf+1, "ARCH"))
				{
					ltoken.type = LTYPE_UARCH;
				}
				else if (!strcmp(ltoken.buf+1, "SYS"))
				{
					ltoken.type = LTYPE_USYS;
				}
				break;
			case 'S':
				if (!strcmp(ltoken.buf+1, "YS"))
				{
					ltoken.type = LTYPE_SYS;
				}
				else if (!strcmp(ltoken.buf+1, "YSFLAG"))
				{
					ltoken.type = LTYPE_SYSFLAG;
				}
				else if (!strcmp(ltoken.buf+1, "ECTIONS"))
				{
					ltoken.type = LTYPE_SECTIONS;
				}
				break;
			}

			break;
		}

		if (isdigit(c))
		{
			while (isalnum(c))
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
