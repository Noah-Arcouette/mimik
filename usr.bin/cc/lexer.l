%{
#include "defs.h"
#include "y.tab.h"

int lineno = 1;

%}

%%

\n {
	lineno++;
}

[ \t] // ignore white space

. {
	return *yytext;
}

%%

int
yywrap (void)
{
	yylex_destroy();
	return 1;
}
