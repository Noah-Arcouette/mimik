#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

void
pre_define (void)
{
	// name...
	int c;
	do
	{
		c = lex_getc();
	} while (!isspace(c) && c != EOF);
	lex_ungetc(c);

	char *name = strdup(lex_token.buf);
	if (!name)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		lex_recover(1, LEX_TOKEN_TYPE_NEWLINE);
		return;
	}

	// whitespace
	lex_nowhitespace();

	// newline
	if (lex_token.type == LEX_TOKEN_TYPE_NEWLINE)
	{
		pre_addMacro(name, "1");
		free(name);
		return;
	}
	// or

	// value...
	do
	{
		c = lex_getc();
	} while (c != '\n' && c != EOF);
	lex_ungetc(c);

	pre_addMacro(name, lex_token.buf);

	free(name);
	lex();
}
