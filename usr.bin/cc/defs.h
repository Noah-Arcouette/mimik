#ifndef __DEFS_H__
#define __DEFS_H__
#include <stdio.h>
enum token {
	// = Key Words =
	EXTERN = 256,
	// = Type =
	INT,
	// = Symbol =
	SYMBOL,
	// = Characters =
	SEMICOLON
};

// lexer.l
extern int    yylex_destroy (void);
extern int    yylex         (void);
extern FILE  *yyin;
extern size_t lineno;
extern char  *yytext;

// cc.c
extern const char *filename;
extern enum token  token;

#endif
