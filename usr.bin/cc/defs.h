#ifndef __DEFS_H__
#define __DEFS_H__
#include <stdio.h>
enum token {
	// = Key Words =
	EXTERN = 256,
	// = Type =
	VOID,
	CHAR,
	SHORT,
	INT,
	// = Qualifier =
	UNSIGNED,
	SIGNED,
	LONG,
	VOLATILE,
	CONST,
	RESTRICT,
	// = Symbol =
	SYMBOL,
	// = Characters =
	SEMICOLON,
	STAR
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
extern size_t      errors;
extern const char *self;

// type.c
struct type
{
	enum {
		TYPE_VOID,
		TYPE_CHAR,
		TYPE_SHORT,
		TYPE_INT,
		TYPE_POINTER,
	} base;
	int isVolatile : 1;
	int isConst    : 1;
	int isRestrict : 1;
	int longness   : 2;
	int isUnsigned : 1; // unsigned?
	struct type *down; // if pointer, this is the sub-type
};

extern void printType (struct type);
extern void freeType  (struct type);

// parser/extern.c
extern int extern_ (void);

// parser/recover.c
extern void recover (void);

// parser/type.c
extern int type (struct type *);

#endif
