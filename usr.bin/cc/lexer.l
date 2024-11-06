%{
#include "defs.h"
#include "y.tab.h"
#include <stdlib.h>

size_t lineno = 1;
%}

%%

[0-9_]+ {
	yylval.value = strtoll(yytext, NULL, 10);
	return VALUE;
}

\n {
	lineno++;
}
[ \t] // ignore

. {
	return *yytext;
}

%%

int
yywrap (void)
{
	return 1;
}

