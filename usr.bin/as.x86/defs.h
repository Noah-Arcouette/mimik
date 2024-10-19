#ifndef __DEFS_H__
#define __DEFS_H__
#include <stddef.h>
#include <stdio.h>

struct yystype
{
	union {
		char  *string;
		size_t value;
	};
	int lineno;
};
#define YYSTYPE struct yystype

// parser.y
extern YYSTYPE yylval;
extern int     errors;

// as.c
extern        char    *filename;
extern const  char    *self;
extern        int      code;
extern struct section *currentSection;
extern struct section *firstSection;
extern struct symbol  *lastFile;
extern struct symbol  *lastSymbol;

// lexer.l
extern int lineno;

// newSymbol.c
struct symbol
{
	char  *name;
	int    flags;
	size_t size;
	size_t val;

	struct symbol *next;
};
extern void newSymbol (const char *, int);

// enterSection.c
struct section
{
	char *name;
	int   flags;

	FILE  *stream; // output stream
	size_t size;
	char  *buffer;
	size_t bssz; // BSS size

	struct symbol *firstSymbol;
	struct gap    *firstGap;

	struct section *next;
};
extern void enterSection (const char *restrict, const char *restrict);

// globalSymbol.c
extern void globalSymbol (const char *);

// emit.c
extern void emit (size_t, int);

// emitGap.c
struct gap
{
	char  *name;
	size_t offset;
	int    flags;

	struct gap *next;
};
extern void emitGap (int, const char *);

// align.c
extern void align (size_t);

// buildSymTab.c
extern void buildSymbolTable (void);

// buildGapTab.c
extern void buildGapTable (void);

#endif
