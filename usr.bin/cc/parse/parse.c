#include "../parse.h"
#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void
parse (struct ast *ast)
{
	ast->type        = AST_TYPE_ROOT;
	ast->root.amount = 0;
	ast->root.node   = NULL;

	preproc_nowhitespace();

	while (lex_token.type != LEX_TOKEN_TYPE_EOF)
	{
		// allocate more room
		ast->root.amount++;
		void *buf = realloc(ast->root.node,
			sizeof(struct ast)*ast->root.amount);
		if (!buf)
		{
			ast->root.amount--;
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			return;
		}
		ast->root.node = buf;

		// uncaught token
		lex_prettyprint(gettext("Uncaught token\n"));
		errors++;
		ast->root.amount--; // remove the empty node
		pre_recover(1, LEX_TOKEN_TYPE_NEWLINE);
		preproc_nowhitespace(); // eat the newline
	}
}
