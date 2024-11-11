#ifndef __DEFS_H__
#define __DEFS_H__
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

struct type
{
	enum {
		TYPE_VOID,
		TYPE_BOOL,
		TYPE_INT
	} base;
};

struct value
{
	struct type type;
	unsigned int variable : 1; // value: is a variable or an immediate value

	union {
		unsigned long long int   value;
		                   char *string;
	};
};
#define YYSTYPE struct value

// printValue.c
extern void printValue (struct value);

// printType.c
extern enum dataTypes {
	DATA_TYPE_ILP32
} dataTypes;
extern void printType (FILE *, struct type); // print the IR form

// compTypes.c
extern int compromiseTypes (struct type *, struct type, struct type);

// lexer.l
extern int    yylex         (void);
extern int    yylex_destroy (void);
extern size_t lineno;

// parser.y
extern int     yyerror (const char *);
extern int     yyparse (void);
extern int     errors;
extern size_t  temps;
extern YYSTYPE yylval;

// cc.c
extern       FILE *fout;
extern const char *filename;
extern const char *self;

// expr.c
extern int expr (struct value *, struct value, struct value, const char *);

// bool.c
extern int boolExpr (struct value *, struct value, struct value, const char *);

// variable.c
struct variable
{
	char       *name;
	struct type type;
	ssize_t     delta;

	size_t      lineno;
	const char *filename;
};

extern struct variable *defineVar (char *, struct type);
extern struct variable *getVar    (char *);

// set.c
extern int setVar (struct variable *, struct value);

// context.c
struct context
{
	struct variable *var;
	size_t           vars;
	size_t           varcp;

	struct context *parent;
};
extern struct context *ctx;

extern void pushContext (void);

// free.c
extern void freeCtx (void);

#endif

