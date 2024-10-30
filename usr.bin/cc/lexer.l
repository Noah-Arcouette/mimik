%{
#include "defs.h"

int lineno = 1;

%}

%%

\n {
	lineno++;
}

%%

int
yywrap (void)
{
	yylex_destroy();
	return 1;
}
