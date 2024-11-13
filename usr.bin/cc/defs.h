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
	STAR,
	LPAREN,
	RPAREN,
	COMA
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

// prototype.c
struct prototype
{
	struct type returnType;
	char       *name; // may be null if the prototype was removed

	size_t      lineno;
	const char *filename;

	struct parameter {
		struct type type;
		char       *name; // warning may be null
	} *parameter;
	size_t parameters;
	size_t parametercp;
};
extern struct prototype *definePrototype (struct type, char *);
extern        void       freePrototype   (struct prototype *);

// context.c
struct context
{
	struct external *external; // external variables
	size_t           externals;
	size_t           externalcp;

	struct prototype *prototype; // function prototypes
	size_t            prototypes;
	size_t            prototypecp;
};
extern struct context *ctx;

extern void freeContexts (void);
extern void freeContext  (struct context *);

// symbols.c
struct symbol
{
	enum {
		SYMBOL_EXTERNAL,
		SYMBOL_PROTOTYPE
	} type;
	union {
		struct external  *external;
		struct prototype *prototype;
	};

	size_t      lineno;
	const char *filename;
};
extern int getSymbol (const char *restrict, struct symbol *restrict);

/*

These don't fail on error
They only fail if they aren't found
Exp:
	extern_ will fail if it doesn't find an extern statement
	extern_ will not fail if the extern statement is malformed

*/

// parser/extern.c, variable externals, and function externals
extern int extern_ (void);

// parser/recover.c, recover to semicolon
extern void recover (void);

// parser/type.c, variable definition type
extern int type (struct type *);

// parser/root.c, the root
extern int root (void);

#endif
