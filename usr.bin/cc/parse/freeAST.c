#include "../parse.h"
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
		fprintf(stderr, "-Root\n");
		break;
	}
}

void
parse_freeAST (struct ast *ast)
{
	_freeAST(ast, 0);
}
