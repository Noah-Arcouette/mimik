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
	COMA,
	LCURLY,
	RCURLY
};

// lexer.l
extern int    yylex_destroy (void);
extern int    yylex         (void);
extern FILE  *yyin;
extern FILE  *yyout;
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

extern void printType   (struct type);
extern void printIRType (struct type);
extern void freeType    (struct type);
extern int  compareType (struct type, struct type);

extern enum dataType {
	LP64,
	ILP64,
	LLP64,
	ILP32,
	LP32
} dataType;

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

	struct parameter *parameter;
	size_t parameters;
	size_t parametercp;

	unsigned int isExternal  : 1;
	unsigned int isMirroring : 1; // is defined already, match the definitions together (just don't allow two implementations)
	struct {
		      size_t parameters; // current parameter defined
		      size_t lineno;
		const char  *filename;
	} mirroring;
};
extern struct prototype *definePrototype   (struct type, char *, int);
extern        int        doneWithPrototype (struct prototype *); // finished modifying a prototype
extern        void       freePrototype     (struct prototype *);

// param.c
struct parameter {
	struct type type;
	char       *name; // warning may be null, not all parameters have names
};

extern int  defineParameter (struct prototype *, struct parameter);
extern void freeParameter   (struct parameter *);

// context.c
struct context
{
	struct external *external; // external variables
	size_t           externals;
	size_t           externalcp;

	struct prototype *prototype; // function prototypes
	size_t            prototypes;
	size_t            prototypecp;

	struct context *parent;
};
extern struct context *ctx;

extern void freeContexts (void);
extern void freeContext  (struct context *);
extern void pushContext  (void);
extern void popContext   (void);

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

These, the following, don't fail on error
They only fail if they aren't found
If there is an error, recovery will be attempted
Exp:
	extern_ will fail if it doesn't find an extern statement
	extern_ will not fail if the extern statement is malformed

*/

// parser/extern.c, variable externals, and function externals
extern int extern_ (void);

// parser/recover.c, recover to semicolon, or closing curly bracket
extern void recover (void);

// parser/type.c, variable definition type
extern int type (struct type *);

// parser/param.c, function PROTOTYPE parameter
extern int parameter (struct parameter *);

// parser/def.c, symbol definition (type symbol ...) any type of definition including functions and global variables
extern int definition (void);

// parser/body.c, function body
extern int body (void);

// parser/root.c, the root
extern int root (void);

#endif
