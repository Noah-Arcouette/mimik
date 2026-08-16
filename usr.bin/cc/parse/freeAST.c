#include "../parse.h"
#include <libintl.h>
#include <stdlib.h>
#include <stdio.h>

static void
_freeAST (struct ast *ast, int depth)
{
	// depth
	for (int i = 0; i<depth; i++)
	{
		fprintf(stderr, "\t");
	}

	switch (ast->type)
	{
	case AST_TYPE_ROOT:
		fprintf(stderr, gettext("-Root:\n"));
		for (unsigned int i = 0; i<ast->root.amount; i++)
		{
			_freeAST(&ast->root.node[i], depth+1);
		}
		free(ast->root.node);
		ast->root.node   = NULL;
		ast->root.amount = 0;
		break;
	}
}

void
parse_freeAST (struct ast *ast)
{
	_freeAST(ast, 0);
}
