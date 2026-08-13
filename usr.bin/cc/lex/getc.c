#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int
lex_getc (void)
{
	// nothing is open
	if (!lex_contexts) return EOF;

	// try to save some time with dereferencing
	static struct lex_context *lc = NULL;
	static int lcs = -1;
	if (lcs != lex_contexts)
	{
		lcs = lex_contexts;
		lc  = &lex_context[lex_contexts-1];
	}

	// get the character
	int c = fgetc(lc->fp);
	if (c == EOF)
	{
		if (ferror(lc->fp))
		{
			switch (lc->type)
			{
			case LEX_CONTEXT_TYPE_NORMAL_FILE:
			case LEX_CONTEXT_TYPE_INCLUDED_FILE:
				fprintf(stderr,
					gettext("%s: Failed to read from file `%s', %s\n"),
					self, lc->name, strerror(errno));
				errors++;
				break;
			}
			return EOF;
		}
		// normal eof
		lex_pop(); // pop the file
		return lex_getc(); // try again
	}
	// else
	if (c == '\\')
	{
		c = getc(lc->fp);
		if (c == '\n')
		{
			// update line information
			lc->lineno++;
			lc->offset = 0;
			lc->size   = 0;
			return lex_getc(); // ignore line splices
		}
		// else
		ungetc(c, lc->fp);
		c = '\\';
	}
	// else

	if (c == '\n')
	{
		// update line information
		lc->lineno++;
		lc->offset = 0;
		lc->size   = 0;
	}
	else lc->size++;
	// else
	// push it onto the lexer buffer

	lex_token.bufsz++;
	if ((lex_token.bufsz+1) > lex_token.bufcp)
	{
		lex_token.bufcp = 3*(lex_token.bufsz+1)/2;
		void *buf = realloc(lex_token.buf, lex_token.bufcp);
		if (!buf)
		{
			lex_token.bufcp = lex_token.bufsz;
			lex_token.bufsz--;
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			return c;
		}
		lex_token.buf = buf;
	}
	lex_token.buf[lex_token.bufsz-1] = c;
	lex_token.buf[lex_token.bufsz  ] = '\0';

	return c; // return the character
}
