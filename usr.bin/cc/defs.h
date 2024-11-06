#ifndef __DEFS_H__
#define __DEFS_H__
#include <stddef.h>

struct value
{
	unsigned long long int value;
};
#define YYSTYPE struct value

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

#endif

