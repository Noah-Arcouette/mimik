%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "y.tab.h"

int lineno = 1;

static void
setString (void)
{
	yylval.string = strdup(yytext);
	if (!yylval.string)
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Errno %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
}

%}

%%

[ \t]*".section"[ \t]* {
	printf("Lexer : SECTION: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SECTION;
}

[ \t]*".file"[ \t]* {
	printf("Lexer : FILE: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DFILE;
}

[ \t]*".globl"[ \t]* {
	printf("Lexer : GLOBAL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return GLOBAL;
}

[ \t]*".code16"[ \t]* {
	printf("Lexer : CODE16: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CODE16;
}
[ \t]*".code32"[ \t]* {
	printf("Lexer : CODE32: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CODE32;
}

[ \t]*".byte"[ \t]* {
	printf("Lexer : BYTE: `%s'\n", yytext);

	yylval.lineno = lineno;
	return BYTE;
}
[ \t]*".short"|".word"[ \t]* {
	printf("Lexer : SHORT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SHORT;
}
[ \t]*".int"[ \t]* {
	printf("Lexer : INT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return INT;
}
[ \t]*".long"[ \t]* {
	printf("Lexer : LONG: `%s'\n", yytext);

	yylval.lineno = lineno;
	return LONG;
}
[ \t]*".asciz"[ \t]* {
	printf("Lexer : ASCIZ: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ASCIZ;
}

[ \t]*".align"[ \t]* {
	printf("Lexer : ALIGN: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ALIGN;
}

"%ax" {
	printf("Lexer : AX: `%s'\n", yytext);

	yylval.lineno = lineno;
	return AX;
}
"%bx" {
	printf("Lexer : BX: `%s'\n", yytext);

	yylval.lineno = lineno;
	return BX;
}
"%es" {
	printf("Lexer : ES: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ES;
}
"%gs" {
	printf("Lexer : GS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return GS;
}
"%ds" {
	printf("Lexer : DS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DS;
}
"%ss" {
	printf("Lexer : SS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SS;
}
"%fs" {
	printf("Lexer : FS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return FS;
}
"%sp" {
	printf("Lexer : SP: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SP;
}
"%bp" {
	printf("Lexer : BP: `%s'\n", yytext);

	yylval.lineno = lineno;
	return BP;
}

"%al" {
	printf("Lexer : AL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return AL;
}
"%ah" {
	printf("Lexer : AH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return AH;
}
"%cl" {
	printf("Lexer : CL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CL;
}
"%ch" {
	printf("Lexer : CH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CH;
}
"%dl" {
	printf("Lexer : DL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DL;
}
"%dh" {
	printf("Lexer : DH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DH;
}

"xor" {
	printf("Lexer : XOR: `%s'\n", yytext);

	yylval.lineno = lineno;
	return XOR;
}

"mov" {
	printf("Lexer : MOV: `%s'\n", yytext);

	yylval.lineno = lineno;
	return MOV;
}

"ljmp" {
	printf("Lexer : LJMP: `%s'\n", yytext);

	yylval.lineno = lineno;
	return LJMP;
}
"jmp" {
	printf("Lexer : JMP: `%s'\n", yytext);

	yylval.lineno = lineno;
	return JMP;
}

"cmp" {
	printf("Lexer : CMP: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CMP;
}

"ret" {
	printf("Lexer : RET: `%s'\n", yytext);

	yylval.lineno = lineno;
	return RET;
}

"jc" {
	printf("Lexer : JC: `%s'\n", yytext);

	yylval.lineno = lineno;
	return JC;
}
"je"|"jz" {
	printf("Lexer : JZ: `%s'\n", yytext);

	yylval.lineno = lineno;
	return JZ;
}

"call" {
	printf("Lexer : CALL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CALL;
}

"int" {
	printf("Lexer : INTERRUPT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return INTERRUPT;
}

[0-9_]+ {
	printf("Lexer : VALUE: `%s'\n", yytext);
	yylval.value = (size_t)strtol(yytext, NULL, 10);

	yylval.lineno = lineno;
	return VALUE;
}

"0x"[a-fA-Z0-9]+ {
	printf("Lexer : VALUE `%s'\n", yytext);
	yylval.value = (size_t)strtol(yytext+2, NULL, 16);

	yylval.lineno = lineno;
	return VALUE;
}

"0b"[a-fA-Z0-9]+ {
	printf("Lexer : VALUE `%s'\n", yytext);
	yylval.value = (size_t)strtol(yytext+2, NULL, 2);

	yylval.lineno = lineno;
	return VALUE;
}

[a-zA-Z0-9\-_.]+ {
	setString();
	printf("Lexer : SYMBOL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SYMBOL;
}

\".*\" {
	yytext++;
	yytext[yyleng-2] = '\0';
	setString();
	printf("Lexer : STRING: `\"%s\"'\n", yytext);

	yylval.lineno = lineno;
	return STRING;
}

; {
	printf("Lexer : NEWLINE\n");

	yylval.lineno = lineno;
	return NEWLINE;
}

\n {
	lineno++;

	printf("Lexer : NEWLINE\n");

	yylval.lineno = lineno;
	return NEWLINE;
}

[ \t\r\f\v] ; // ignore

. {
	printf("Lexer : CHAR: `%s'\n", yytext);

	yylval.lineno = lineno;
	return *yytext;
}

%%

int
yywrap (void)
{
	return 1;
}
