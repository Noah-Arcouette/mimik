#ifndef __LEX_H__
#define __LEX_H__
#include <stdio.h>
#include <wchar.h>

enum ltype
{
	// symbols
	LTYPE_OPEN_CURLY  = L'{',
	LTYPE_CLOSE_CURLY = L'}',
	LTYPE_EQUAL       = L'=',
	LTYPE_SEMICOLON   = L';',
	LTYPE_COLON       = L':',
	LTYPE_OPEN_PAREN  = L'(',
	LTYPE_CLOSE_PAREN = L')',
	LTYPE_PLUS        = L'+',
	LTYPE_SUBTRACT    = L'-',
	LTYPE_DIVIDE      = L'/',
	LTYPE_MULTIPLY    = L'*',
	// others
	LTYPE_EOF = 0xff,
	LTYPE_UNKNOWN,
	// macros
	LTYPE_ENTRY,
	LTYPE_ARCH,
	LTYPE_UARCH,
	LTYPE_ALIGN,
	LTYPE_ARCHFLAG,
	LTYPE_SYS,
	LTYPE_USYS,
	LTYPE_SYSFLAG,
	LTYPE_SECTIONS,
	LTYPE_BYTE,
	LTYPE_SHORT,
	LTYPE_LONG,
	LTYPE_QUAD,
	LTYPE_NOLOAD,
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

	long     bufcp; // capacity of the buffer
	wchar_t *buf;  // le buffer
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

/**
 * Whether or not `*` counts as a symbol letter
 * @file lex/lex.c
 */
extern int lex_symbolCanGlob;

#endif
