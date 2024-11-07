#ifndef __DEFS_H__
#define __DEFS_H__
#include <stddef.h>
#include <stdio.h>

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
	
	unsigned long long int value;
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

// expr.c
extern int expr (struct value *, struct value, struct value, const char *);

// bool.c
extern int boolExpr (struct value *, struct value, struct value, const char *);

#endif

