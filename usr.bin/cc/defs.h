#ifndef __DEFS_H__
#define __DEFS_H__

// lexer.l
extern int lineno;

// parser.y
struct yystype
{
	union {
		long long value;
		char     *string;
	};

	int lineno;
};
#define YYSTYPE struct yystype
extern YYSTYPE yylval;

// cc.c
extern const char *filename;
extern       int   errors;
extern const char *self;

#endif

