%{
#include "defs.h"
#include "y.tab.h"
#include <stdlib.h>

size_t lineno = 1;
%}

%%

"goto" { // = Keywords =
	return GOTO;
}
"if" {
	return IF;
}

"int" { // = Types =
	return INT;
}

">=" { // = Multicharacter operations =
	return GTE;
}
"<=" {
	return LTE;
}
"==" {
	return EQU;
}
"!=" {
	return NEQ;
}
"&&" {
	return BOOL_AND;
}
"||" {
	return BOOL_OR;
}

[0-9_]+ { // = Numbers =
	yylval.type.base = TYPE_INT;
	yylval.variable  = 0;
	yylval.value     = strtoll(yytext, NULL, 10);
	return VALUE;
}

[a-zA-Z_]+ { // = Symbol =
	yylval.string = strdup(yytext);
	return SYMBOL;
}

\n {
	lineno++;
}
[ \t] // ignore

. {
	yylval.type.base = TYPE_VOID;
	return *yytext;
}

%%

int
yywrap (void)
{
	return 1;
}

