#ifndef __AST_H__
#define __AST_H__
#include <stdio.h>

/// @brief A single AST node
struct ast
{
	// prettyprint information
	// node type
	// node values
};

/**
 * Generate an AST from an input file
 * @param path The file name / path
 * @param fp The file pointer to use
 * @returns An AST node, or null upon error
 * @file ast/generate.c
 */
extern struct ast *ast_generate (const char *path, FILE *fp);

#endif
