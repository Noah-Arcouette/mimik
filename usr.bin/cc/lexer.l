%{
#include "defs.h"
#include <stddef.h>

size_t lineno = 1;
%}

%%

"extern" { // = Key words =
	return EXTERN;
}
"return" {
	return RETURN;
}
"if" {
	return IF;
}
"else" {
	return ELSE;
}
"while" {
	return WHILE;
}
"break" {
	return BREAK;
}
"continue" {
	return CONTINUE;
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
"const" {
	return CONST;
}
"restrict" {
	return RESTRICT;
}

[a-zA-Z_]* { // = Symbol =
	return SYMBOL;
}

[0-9_]* {
	return IMM_INT;
}

\n {
	lineno++;
}

[ \t] // ignore

"=" { // = Setting =
	return EQUAL;
}

; { // = characters =
	return SEMICOLON;
}
"*" {
	return STAR;
}
"/" {
	return DIV;
}
"%" {
	return MOD;
}
"+" {
	return PLUS;
}
"-" {
	return MINUS;
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
"{" {
	return LCURLY;
}
"}" {
	return RCURLY;
}
"[" {
	return LSQUARE;
}
"]" {
	return RSQUARE;
}

%%

int
yywrap (void)
{
	return 1;
}
