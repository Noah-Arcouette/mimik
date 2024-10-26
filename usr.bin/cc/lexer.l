%{

#include "y.tab.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>

int lineno = 1;

%}

%%

[0-9][0-9_]* { // = Values =
	fprintf(stderr, "Lexer : VALUE: `%s'\n", yytext);
	yylval.value = strtoll(yytext, NULL, 10);

	yylval.lineno = lineno;
	return VALUE;
}
"0x"[0-9a-f][0-9a-f_]* {
	fprintf(stderr, "Lexer : VALUE: `%s'\n", yytext);
	yylval.value = strtoll(yytext, NULL, 16);

	yylval.lineno = lineno;
	return VALUE;
}
"0b"[01][01_]* {
	fprintf(stderr, "Lexer : VALUE: `%s'\n", yytext);
	yylval.value = strtoll(yytext, NULL, 2);

	yylval.lineno = lineno;
	return VALUE;
}
"0"[0-6][0-6_]* {
	fprintf(stderr, "Lexer : VALUE: `%s'\n", yytext);
	yylval.value = strtoll(yytext, NULL, 7);

	yylval.lineno = lineno;
	return VALUE;
}

\n { // = white space =
	lineno++; // ignore newline, but increment to a newline
}

[ \t]* ; // ignore white space

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

