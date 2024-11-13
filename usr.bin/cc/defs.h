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
	unsigned int isVolatile : 1;
	unsigned int isConst    : 1;
	unsigned int isRestrict : 1;
	unsigned int longness   : 2;
	unsigned int isUnsigned : 1; // unsigned?
	struct type *down; // if pointer, this is the sub-type
};

extern void printType (struct type);
extern void freeType  (struct type);

// external.c
struct external
{
	struct type type;
	char       *name;

	size_t      lineno;
	const char *filename;
};
extern int  defineExternal (char *name, struct type type);
extern void freeExternal   (struct external *);

// context.c
struct context
{
	struct external *external; // external variables
	size_t           externals;
	size_t           externalcp;
};
extern struct context *ctx;

extern void freeContexts (void);
extern void freeContext  (struct context *);

// symbols.c
struct symbol
{
	enum {
		SYMBOL_EXTERNAL
	} type;
	union {
		struct external *external;
	};

	size_t      lineno;
	const char *filename;
};
extern int getSymbol (const char *restrict, struct symbol *restrict);

// parser/extern.c
extern int extern_ (void);

// parser/recover.c
extern void recover (void);

// parser/type.c
extern int type (struct type *);

#endif
