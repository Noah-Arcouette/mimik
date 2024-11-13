%{
#include "defs.h"
#include <stddef.h>

size_t lineno = 1;
%}

%%

"extern" { // = Key words =
	return EXTERN;
}

"void" { // = Types =
	return VOID;
}
"char" {
	return CHAR;
}
"short" {
	return SHORT;
}
"int" {
	return INT;
}
"unsigned" { // = Qualifiers =
	return UNSIGNED;
}
"signed" {
	return SIGNED;
}
"long" {
	return LONG;
}
"volatile" {
	return VOLATILE;
}
"const" {
	return CONST;
}
"restrict" {
	return RESTRICT;
}

[a-zA-Z_]* { // = Symbol =
	return SYMBOL;
}

\n {
	lineno++;
}

[ \t] // ignore

; { // = characters =
	return SEMICOLON;
}
"*" {
	return STAR;
}
"(" {
	return LPAREN;
}
")" {
	return RPAREN;
}
"," {
	return COMA;
}

%%

int
yywrap (void)
{
	return 1;
}
