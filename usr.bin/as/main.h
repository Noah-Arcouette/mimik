#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>

/**
 * The name of the current program
 * @file main.c
 */
extern const char *self;

/// @brief The command line argument options
extern struct arguments
{
	const char *outputfile;
} arguments;

/**
 * Parse the command line arguments
 * @param argc The argument count
 * @param argv The argument values
 * @returns True if an error occurred
 * @file args.c
 */
extern int args (int argc, char *argv[]);

/// @brief A lexer token type
enum tokenType
{
	TOK_EOF,
	TOK_UNKNOWN,
	TOK_NEWLINE,
	TOK_COLON,
	// directives
	TOK_ARCH,
	TOK_SECTION,
	TOK_GLOBAL,
	// values
	TOK_SYMBOL
};

/// @brief A lexer token
struct token
{
	enum tokenType type;

	long lineno; // the current line number
	long offset; // the current character offset
	long size;   // the size of the current token buffer

	long  bufcp; // the buffer capacity
	char *buf;   // the token buffer
};

/**
 * Parse a token from a file
 * @param filename The name of the current file
 * @param fp The file to gain the token from
 * @param tok The token to fill
 * @returns True upon error
 * @file lex.c
 */
extern int lex (const char *filename, FILE *fp, struct token *tok);

/**
 * Create a token
 * @param tok The token to initialize
 * @file token.c
 */
extern void createToken (struct token *tok);

/**
 * Reset a token to the initial state
 * @param tok The token to reset
 * @file token.c
 */
extern void resetToken (struct token *tok);

/**
 * Free the data from a token
 * @param tok The token to free
 * @file token.c
 */
extern void destroyToken (struct token *tok);

#endif
