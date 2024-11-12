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
extern void printCType (FILE *, struct type);

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
extern int  expr      (struct value *, struct value, struct value, const char *);
extern void unaryExpr (struct value *, struct value,               const char *);

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

	struct label *label;
	size_t        labels;
	size_t        labelcp;

	struct context *parent;
};
extern struct context *ctx;

extern void pushContext (void);
extern void popContext  (void);

// free.c
extern void freeCtx         (struct context *);
extern void freeAllContexts (void);

// labels.c
struct label
{
	char  *name;
	size_t label;

	size_t      lineno;
	const char *filename;
};
extern size_t labelTemp;

extern int  defineLabel (char *);
extern void gotoLabel   (char *);

// info.c
struct info
{
	size_t start;
	size_t end;
	size_t elif; // for if statements

	struct info *parent;
};
extern struct info *info;

extern void infoPush (struct info);
extern void infoPop  (void);
extern void freeInfo (void);

#endif

