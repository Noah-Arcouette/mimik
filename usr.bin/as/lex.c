#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"

/**
 * Push a character onto a token, ensuring that the buffer stays null terminated
 * @param tok The token
 * @param c The character
 * @file lex.c
 */
static void
_pushc (struct token *tok, char c)
{
	tok->size++;
	if ((tok->size+1) > tok->bufcp)
	{
		tok->bufcp = (3*(tok->size+1))/2;
		void *buf = realloc(tok->buf, tok->bufcp);
		if (!buf)
		{
			fprintf(stderr, gettext("%s: Failed to allocate memory\n"), self);
			errors++;
			return;
		}
		tok->buf = buf;
	}
	tok->buf[tok->size-1] = c;
	tok->buf[tok->size  ] = '\0';
}

void
lex (const char *filename, FILE *fp, struct token *tok)
{
_try_again:
	tok->offset += tok->size;
	tok->size    = 0;

	int c = fgetc(fp);

	switch (c)
	{
	case ' ':
	case '\t':
		tok->size++;
		goto _try_again;
	case '\n':
		tok->lineno++;
		tok->offset = 0;
		tok->type = TOK_NEWLINE;
		break;
	case ':':
		_pushc(tok, c);
		tok->type = TOK_COLON;
		break;
	case EOF:
		tok->type = TOK_EOF;
		break;
	default:
		if (isalpha(c) || c == '.' || c == '_')
		{
			while (isalnum(c) || c == '.' || c == '_')
			{
				_pushc(tok, c);
				c = fgetc(fp);
			}
			ungetc(c, fp); // unget the non-matching character

			if (!strcmp(tok->buf, ".arch"))
			{
				tok->type = TOK_ARCH;
				break;
			}
			if (!strcmp(tok->buf, ".section"))
			{
				tok->type = TOK_SECTION;
				break;
			}
			if (!strcmp(tok->buf, ".global"))
			{
				tok->type = TOK_GLOBAL;
				break;
			}

			tok->type = TOK_SYMBOL;
			break;
		}
		// else

		_pushc(tok, c);
		tok->type = TOK_UNKNOWN;
		break;
	}
}
