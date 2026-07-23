#ifndef __LEX_H__
#define __LEX_H__
#include <stdio.h>

enum ltype
{
	// symbols
	LTYPE_OPEN_CURLY  = '{',
	LTYPE_CLOSE_CURLY = '}',
	LTYPE_EQUAL       = '=',
	LTYPE_SEMICOLON   = ';',
	LTYPE_COLON       = ':',
	LTYPE_OPEN_PAREN  = '(',
	LTYPE_CLOSE_PAREN = ')',
	LTYPE_PLUS        = '+',
	LTYPE_SUBTRACT    = '-',
	LTYPE_DIVIDE      = '/',
	LTYPE_MULTIPLY    = '*',
	// others
	LTYPE_EOF = 0xff,
	LTYPE_UNKNOWN,
	// macros
	LTYPE_ENTRY,
	LTYPE_ARCH,
	LTYPE_UARCH,
	LTYPE_ARCHFLAG,
	LTYPE_SYS,
	LTYPE_USYS,
	LTYPE_SYSFLAG,
	LTYPE_SECTIONS,
	// values
	LTYPE_SYMBOL,
	LTYPE_INTEGER
};

struct ltoken
{
	enum ltype type;

	long lineno; // line number
	long offset; // character offset
	long length; // length of the token

	long bufcp; // capacity of the buffer
	char *buf;  // le buffer
};

/**
 * The current output token
 * @file lex/lex.c
 */
extern struct ltoken ltoken;

/**
 * The input to the lexer
 * @file lex/lex.c
 */
extern FILE *lfp;
extern const char *lfilename;

/**
 * The main lexer function, will update ltoken from lfp
 * @file lex/lex.c
 */
extern void lex (void);

/**
 * Free all lexer related data, other than closing the input file
 * @file lex/lex_free.c
 */
extern void lex_free (void);

/**
 * Print a file debug line
 * @param fmt printf format string
 * @file lex/prettyprint.c
 */
extern void prettyprint (const char *fmt, ...);

/**
 * Recover to a new line
 * @file lex/recover.c
 */
extern void recover (void);

#endif
