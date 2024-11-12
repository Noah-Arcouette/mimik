%{
#include "defs.h"
#include <stddef.h>

size_t lineno = 1;
%}

%%

"extern" { // = Key words =
	return EXTERN;
}

"int" { // = Types =
	return INT;
}

[a-zA-Z_]* { // = Symbol =
	return SYMBOL;
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
