%{
#include "defs.h"
#include "y.tab.h"
#include <limits.h>

int lineno = 1;

%}

%%

[0-9_]+ { // = Value = : integer
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_VALUE;

	yylval.valueType.signness = 1;
	yylval.valueType.type     = TYPE_INT;
	yylval.value.value        = (long long int)strtoll(yytext, NULL, 10);

	return VALUE;
}
[0-9_]+[Uu] {
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_VALUE;

	yylval.valueType.type = TYPE_INT;
	yylval.value.uvalue   = (unsigned long long int)strtoll(yytext, NULL, 10);

	return VALUE;
}

"&&" { // = boolean operations =
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_BOOL_AND;

	return BOOL_AND;
}
"||" {
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_BOOL_OR;

	return BOOL_OR;
}
"==" {
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_BOOL_EQ;

	return BOOL_EQ;
}
"!=" {
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_BOOL_NEQ;

	return BOOL_NEQ;
}
">=" {
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_BOOL_GTE;

	return BOOL_GTE;
}
"<=" {
	memset(&yylval, 0, sizeof(struct node));
	yylval.nodeType = NODE_BOOL_LTE;

	return BOOL_LTE;
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
