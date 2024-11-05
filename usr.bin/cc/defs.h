#ifndef __DEFS_H__
#define __DEFS_H__

// lexer.l
extern int  yylex         (void);
extern void yylex_destroy (void);

// parser.y
extern int yyerror (const char *);
extern int yyparse (void);
extern int errors;

#endif

