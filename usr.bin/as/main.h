#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>

/**
 * The name of the current program
 * @file main.c
 */
extern const char *self;

/**
 * The total errors encountered
 * @file main.c
 */
extern int errors;

/// @brief The command line argument options
extern struct arguments
{
	const char *outputfile;
} arguments;

/**
 * Parse the command line arguments
 * @param argc The argument count
 * @param argv The argument values
 * @file args.c
 */
extern void args (int argc, char *argv[]);

/// @brief A lexer token type
enum tokenType
{
	TOK_EOF,
	TOK_UNKNOWN,
	TOK_NEWLINE,
	TOK_COLON,
	TOK_SEMICOLON,
	// directives
	TOK_ARCH,
	TOK_UARCH,
	TOK_ARCHFLAG,
	TOK_SYS,
	TOK_USYS,
	TOK_SYSFLAG,
	TOK_SECTION,
	TOK_GLOBAL,
	// values
	TOK_SYMBOL,
	TOK_REGISTER
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
 * The current file pointer to lex
 * @file lex.c
 */
extern FILE *lfp;

/**
 * The current file name being lexed
 * @file lex.c
 */
extern const char *lfilename;

/**
 * The current token
 * @file token.c
 */
extern struct token ltok;

/**
 * Parse the token from a file
 * @file lex.c
 */
extern void lex (void);

/**
 * Reset the token to the initial state
 * @file token.c
 */
extern void resetToken (void);

/**
 * Free the data from the token
 * @file token.c
 */
extern void destroyToken (void);

/**
 * Parse the current file
 * @file parse.c
 */
extern void parse (void);

/**
 * Recover to a newline or EOF
 * @file recover.c
 */
extern void recover (void);

/**
 * Print a message about the current token
 * @param fmt The format string
 * @file prettyprint.c
 */
extern void prettyprint (const char *fmt, ...);

/**
 * Emit the output file
 * @file writeOutput.c
 */
extern void writeOutput (void);

#endif
