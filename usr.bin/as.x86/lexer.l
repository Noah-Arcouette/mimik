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

[ \t]*".section"[ \t]* { // = Directives =
	printf("Lexer : SECTION: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SECTION;
}
[ \t]*".file"[ \t]* {
	printf("Lexer : FILE: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DFILE;
}
[ \t]*".glob"a?"l"[ \t]* {
	printf("Lexer : GLOBAL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return GLOBAL;
}

[ \t]*".code16"[ \t]* { // = Code Type =
	printf("Lexer : CODE16: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CODE16;
}
[ \t]*".code32"[ \t]* {
	printf("Lexer : CODE32: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CODE32;
}

[ \t]*".byte"[ \t]* { // = Raw Data =
	printf("Lexer : BYTE: `%s'\n", yytext);

	yylval.lineno = lineno;
	return BYTE;
}
[ \t]*".short"|".word"[ \t]* {
	printf("Lexer : SHORT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return WORD;
}
[ \t]*".int"[ \t]* {
	printf("Lexer : INT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DWORD;
}
[ \t]*".long"[ \t]* {
	printf("Lexer : LONG: `%s'\n", yytext);

	yylval.lineno = lineno;
	return QWORD;
}
[ \t]*".asciz"[ \t]* {
	printf("Lexer : ASCIZ: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ASCIZ;
}
[ \t]*".align"[ \t]* { // - Alignment -
	printf("Lexer : ALIGN: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ALIGN;
}

"%es" { // = Segment Registers =
	printf("Lexer : ES: `%s'\n", yytext);

	yylval.lineno = lineno;
	return ES;
}
"%cs" {
	printf("Lexer : CS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CS;
}
"%ss" {
	printf("Lexer : SS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SS;
}
"%ds" {
	printf("Lexer : DS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DS;
}
"%fs" {
	printf("Lexer : FS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return FS;
}
"%gs" {
	printf("Lexer : GS: `%s'\n", yytext);

	yylval.lineno = lineno;
	return GS;
}

"%ax" { // = 16bit registers =
	printf("Lexer : AX: `%s'\n", yytext);

	yylval.lineno = lineno;
	return AX;
}
"%cx" {
	printf("Lexer : CX: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CX;
}
"%dx" {
	printf("Lexer : DX: `%s'\n", yytext);
	
	yylval.lineno = lineno;
	return DX;
}
"%bx" {
	printf("Lexer : BX: `%s'\n", yytext);
	
	yylval.lineno = lineno;
	return BX;
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
"%si" {
	printf("Lexer : SI: `%s'\n", yytext);

	yylval.lineno = lineno;
	return SI;
}
"%di" {
	printf("Lexer : DI: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DI;
}

"%al" { // = 8bit Registers =
	printf("Lexer : AL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return AL;
}
"%cl" {
	printf("Lexer : CL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CL;
}
"%dl" {
	printf("Lexer : DL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DL;
}
"%bl" {
	printf("Lexer : BL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return BL;
}
"%ah" {
	printf("Lexer : AH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return AH;
}
"%ch" {
	printf("Lexer : CH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CH;
}
"%dh" {
	printf("Lexer : DH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return DH;
}
"%bh" {
	printf("Lexer : BH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return BH;
}

"xor" {
	printf("Lexer : XOR: `%s'\n", yytext);

	yylval.lineno = lineno;
	return XOR;
}
"not" {
	printf("Lexer : NOT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return NOT;
}

"mov" {
	printf("Lexer : MOV: `%s'\n", yytext);

	yylval.lineno = lineno;
	return MOV;
}
"movb" {
	printf("Lexer : MOVB `%s'\n", yytext);

	yylval.lineno = lineno;
	return MOVB;
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
"cmpb" {
	printf("Lexer : CMPB: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CMPB;
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
"jl" {
	printf("Lexer : JL `%s'\n", yytext);

	yylval.lineno = lineno;
	return JL;
}
"jg" {
	printf("Lexer : JG `%s'\n", yytext);

	yylval.lineno = lineno;
	return JG;
}

"call" {
	printf("Lexer : CALL: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CALL;
}

"int" {
	printf("Lexer : INTERRUPT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return INT;
}
"cli" {
	printf("Lexer : CLI: `%s'\n", yytext);

	yylval.lineno = lineno;
	return CLI;
}
"sti" {
	printf("Lexer : STI: `%s'\n", yytext);

	yylval.lineno = lineno;
	return STI;
}
"hlt" {
	printf("Lexer : HLT: `%s'\n", yytext);

	yylval.lineno = lineno;
	return HLT;
}

"inc" {
	printf("Lexer : INC: `%s'\n", yytext);

	yylval.lineno = lineno;
	return INC;
}

"push" {
	printf("Lexer : PUSH: `%s'\n", yytext);

	yylval.lineno = lineno;
	return PUSH;
}
"pop" {
	printf("Lexer : POP: `%s'\n", yytext);

	yylval.lineno = lineno;
	return POP;
}
"pushf" {
	printf("Lexer : PUSHF: `%s'\n", yytext);

	yylval.lineno = lineno;
	return PUSHF;
}
"popf" {
	printf("Lexer : POPF: `%s'\n", yytext);

	yylval.lineno = lineno;
	return POPF;
}

[0-9_]+ {
	printf("Lexer : VALUE: `%s'\n", yytext);
	yylval.value = (size_t)strtol(yytext, NULL, 10);

	yylval.lineno = lineno;
	return VALUE;
}

"0x"[a-fA-Z0-9_]+ {
	printf("Lexer : VALUE `%s'\n", yytext);
	yylval.value = (size_t)strtol(yytext+2, NULL, 16);

	yylval.lineno = lineno;
	return VALUE;
}

"0b"[01_]+ {
	printf("Lexer : VALUE `%s'\n", yytext);
	yylval.value = (size_t)strtol(yytext+2, NULL, 2);

	yylval.lineno = lineno;
	return VALUE;
}

"'"."'" {
	printf("Lexer : VALUE `%s'\n", yytext);
	yylval.value = (size_t)(*yytext);

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
