#ifndef __PARSE_H__
#define __PARSE_H__

enum astType
{
	AST_TYPE_ROOT
};

struct ast
{
	enum astType type;

	union
	{
		struct
		{
			unsigned int amount; // amount of nodes
			struct ast  *node; // the nodes
		} root;
	};
};

/**
 * The root of the c parser
 * @file parse/parse.c
 * @param ast The ast node
 */
extern void parse (struct ast *ast);

/**
 * Free the ast node
 * @param ast The ast node in question
 * @file parse/freeAST.c
 */
extern void parse_freeAST (struct ast *ast);

#endif
