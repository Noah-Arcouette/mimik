%{

#include "y.tab.h"
#include "defs.h"

int lineno = 1;

%}

%%

\n {
	lineno++; // ignore newline, but increment to a newline
}

[ \t]* ; // isgnore white space

. {
	fprintf(stderr, "Lexer : CHAR: `%s'\n", yytext);

	return *yytext; // return the single character
}

%%

int
yywrap (void)
{
	return 1;
}

