%{
#include "defs.h"
#include "y.tab.h"
#include <limits.h>

int lineno = 1;

%}

%%

[0-9_]+ { // = Value = : unsigned integer
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_VALUE;
	unsigned long long v = (unsigned long long)strtoll(yytext, NULL, 10); // get value

	// get type
	yylval.valueType.longness = 2;
	yylval.valueType.type     = TYPE_INT;
	yylval.value.uvalue       = (unsigned long long int)v;

	return VALUE;
}

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
