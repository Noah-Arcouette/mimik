%{

#include "defs.h"
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

int lineno = 1;

static void
setString ()
{
	// duplication string
	yylval.string = strdup(yytext);

	if (!yylval.string) // check for error
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
}

%}

%%

"void" { // = Types =
	fprintf(stderr, "Lexer : VOID: `%s'\n", yytext);

	yylval.lineno = lineno;
	return VOID;
}
"char" {
	fprintf(stderr, "Lexer : CHAR: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CHAR;
}
"short" {
	fprintf(stderr, "Lexer : SHORT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SHORT;
}
"int" {
	fprintf(stderr, "Lexer : INT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return INT;
}
"long" {
	fprintf(stderr, "Lexer : LONG: `%s'\n", yytext);

	yylval.lineno = lineno;
	return LONG;
}
"long int" {
	fprintf(stderr, "Lexer : LONG INT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return LONG;
}
"long long" {
	fprintf(stderr, "Lexer : LONG LONG: `%s'\n", yytext);

	yylval.lineno = lineno;
	return LONG_LONG;
}

"unsigned" { // = Qualifiers =
	fprintf(stderr, "Lexer : UNSIGNED: `%s'\n", yytext);

	yylval.lineno = lineno;
	return UNSIGNED;
}
"signed" {
	fprintf(stderr, "Lexer : SIGNED: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SIGNED;
}
"const" {
	fprintf(stderr, "Lexer : CONST: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CONST;
}
"volatile" {
	fprintf(stderr, "Lexer : VOLATILE: `%s'\n", yytext);

	yylval.lineno = lineno;
	return VOLATILE;
}

"struct" { // = Structure Types =
	fprintf(stderr, "Lexer : STRUCT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return STRUCT;
}
"union" {
	fprintf(stderr, "Lexer : UNION: `%s'\n", yytext);

	yylval.lineno = lineno;
	return UNION;
}
"enum" {
	fprintf(stderr, "Lexer : ENUM: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ENUM;
}

"return" { // = Keywords =
	fprintf(stderr, "Lexer : RETURN: `%s'\n", yytext);

	yylval.lineno = lineno;
	return RETURN;
}

"0"[0-6][0-6_]* { // = Values =
	fprintf(stderr, "Lexer : VALUE: `%s'\n", yytext);
	yylval.value = strtoll(yytext, NULL, 7);

	yylval.lineno = lineno;
	return VALUE;
}
[0-9][0-9_]* {
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

[a-zA-Z0-9_]* { // = Symbol =
	fprintf(stderr, "Lexer : SYMBOL: `%s'\n", yytext);
	setString();

	yylval.lineno = lineno;
	return SYMBOL;
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

