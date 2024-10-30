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
	if (v >= UCHAR_MAX)
	{
		yylval.valueType.type = TYPE_CHAR;
		yylval.value.uc       = (unsigned char)v;
	}
	else if (v <= USHRT_MAX)
	{
		yylval.valueType.type = TYPE_SHORT;
		yylval.value.us       = (unsigned short)v;
	}
	else if (v <= UINT_MAX)
	{
		yylval.valueType.type = TYPE_INT;
		yylval.value.ui       = (unsigned int)v;
	}
	else if (v <= ULONG_MAX)
	{
		yylval.valueType.longness = 1;
		yylval.valueType.type     = TYPE_INT;
		yylval.value.ul           = (unsigned long int)v;
	}
	else if (v <= ULLONG_MAX)
	{
		yylval.valueType.longness = 2;
		yylval.valueType.type     = TYPE_INT;
		yylval.value.ull          = (unsigned long long int)v;
	}

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
