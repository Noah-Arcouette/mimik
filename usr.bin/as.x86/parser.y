%{

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include <mio.h>
#include <mio-x86.h>

// tell yacc to prevent leaks and free data when done
#define YY_NO_LEAKS

int errors = 0;

// Bison support
extern int  yylex   (void);
extern void yyerror (const char *);

%}

%token SECTION DFILE GLOBAL
%token CODE16 CODE32
%token BYTE WORD DWORD QWORD ASCIZ ALIGN
%token ES CS SS DS FS GS
%token AX CX DX BX BP SP SI DI
%token AL CL DL BL AH CH DH BH

%token XOR NOT
%token MOV
%token MOVB
%token LJMP JMP CALL
%token JZ JC JL JG
%token RET
%token CMP CMPB
%token INT STI CLI HLT
%token INC
%token PUSH POP PUSHF POPF
%token STRING SYMBOL GLOBAL
%token VALUE
%token NEWLINE
%start program

%destructor { free($$.string); } STRING SYMBOL
%%

program:
	  program NEWLINE
	| program section
	| program ALIGN VALUE NEWLINE { align($3.value); }

	| program SYMBOL ':'           { newSymbol($2.string, MIO_SYMLIST_TYPE_ADDRESS); free($2.string); }
	| program DFILE STRING NEWLINE { newSymbol($3.string, MIO_SYMLIST_TYPE_FILE   ); free($3.string); }

	| program CODE16 NEWLINE { code = 16; }
	| program CODE32 NEWLINE {
		code = 32;
		if (header.uarch < MIO_UARCH_I386)
		{
			fprintf(stderr, "%s:%d: Warning 32bit code promotes the micro-architecture to I386.\n", filename, $2.lineno);
			header.uarch = MIO_UARCH_I386;
		}
	}

	| program data

	| program GLOBAL SYMBOL NEWLINE { globalSymbol($3.string); free($3.string); }

	| program xor NEWLINE
	| program not NEWLINE

	| program mov NEWLINE
	| program movb NEWLINE

	| program jmp NEWLINE
	| program call NEWLINE
	| program jcc NEWLINE
	| program ret NEWLINE
	| program cmp NEWLINE
	| program inc NEWLINE

	| program STI NEWLINE { emit(0xfb, BYTE); }
	| program CLI NEWLINE { emit(0xfa, BYTE); }
	| program HLT NEWLINE { emit(0xf4, BYTE); }
	| program INT '$' VALUE NEWLINE {
		emit(0xcd,     BYTE);
		emit($4.value, BYTE);
	}

	| program push_pop NEWLINE

	| program error NEWLINE { yyerrok; yyclearin; }
	|
	;

section:
	  SECTION SYMBOL NEWLINE            { enterSection($2.string, ""       ); free($2.string);                  }
	| SECTION SYMBOL ',' STRING NEWLINE { enterSection($2.string, $4.string); free($2.string); free($4.string); }
	;

data:
	   BYTE VALUE  { emit($2.value,  BYTE); }
	|  WORD VALUE  { emit($2.value,  WORD); }
	| DWORD VALUE  { emit($2.value, DWORD); }
	| QWORD VALUE  { emit($2.value, QWORD); }
	|  WORD SYMBOL { emitGap(MIO_GAP_ABSOLUTE_WORD,  $2.string); free($2.string); }
	| QWORD SYMBOL { emitGap(MIO_GAP_ABSOLUTE_QWORD, $2.string); free($2.string); }
	| ASCIZ STRING {
		for (size_t i = 0; $2.string[i]; i++)
		{
			emit($2.string[i], BYTE);
		}
		emit(0, BYTE);
		free($2.string);
	}
	;

jmp:
	LJMP '$' VALUE ',' '$' SYMBOL {
		emit(0xea, BYTE);

		if (code == 16)
		{
			emitGap(MIO_GAP_RELATIVE_WORD|MIO_GAP_FLAG_EXECUTE, $6.string);
			emit($3.value, WORD);
		}
		else
		{
			emitGap(MIO_GAP_RELATIVE_DWORD|MIO_GAP_FLAG_EXECUTE, $6.string);
			emit($3.value, DWORD);
		}
		free($6.string);
	}
	| JMP '$' VALUE ',' '$' SYMBOL {
		emit(0xea, BYTE);
		emitGap(MIO_GAP_RELATIVE_WORD|MIO_GAP_FLAG_EXECUTE, $6.string);
		free($6.string);
		emit($3.value, WORD);
	}
	| JMP SYMBOL {
		emit(0xe9, BYTE);
		emitGap(MIO_GAP_RELATIVE_WORD|MIO_GAP_FLAG_EXECUTE, $2.string);
		free($2.string);
	}
	;

call:
	CALL SYMBOL {
		emit(0xe8, BYTE);
		emitGap(MIO_GAP_RELATIVE_WORD|MIO_GAP_FLAG_EXECUTE, $2.string);
		free($2.string);
	}
	;

jcc:
	JZ SYMBOL {
		emit(0x74, BYTE);
		emitGap(MIO_GAP_RELATIVE_BYTE|MIO_GAP_FLAG_EXECUTE, $2.string);
		free($2.string);
	}
	| JC SYMBOL {
		emit(0x72, BYTE);
		emitGap(MIO_GAP_RELATIVE_BYTE|MIO_GAP_FLAG_EXECUTE, $2.string);
		free($2.string);
	}
	| JL SYMBOL {
		emit(0x7c, BYTE);
		emitGap(MIO_GAP_RELATIVE_BYTE|MIO_GAP_FLAG_EXECUTE, $2.string);
		free($2.string);
	}
	| JG SYMBOL {
		emit(0x7f, BYTE);
		emitGap(MIO_GAP_RELATIVE_BYTE|MIO_GAP_FLAG_EXECUTE, $2.string);
		free($2.string);
	}
	;

ret:
	RET {
		emit(0xc3, BYTE);
	}
	;

cmp:
	CMP '$' SYMBOL ',' AL {
		emit(0x3c, BYTE);
		emitGap(MIO_GAP_ABSOLUTE_BYTE|MIO_GAP_FLAG_READ, $3.string);
		free($3.string);
	}
	| CMP '$' VALUE ',' AL {
		emit(0x3c, BYTE);
		emit($2.value, BYTE);
	}
	| CMP '$' SYMBOL ',' reg16 {
		emit(0x81, BYTE);
		emit(
			0b11111000 | $5.value,
			BYTE
		);
		emitGap(MIO_GAP_ABSOLUTE_WORD|MIO_GAP_FLAG_READ, $3.string);
		free($3.string);
	}
	| CMP '$' VALUE ',' reg16 {
		emit(0x81, BYTE);
		emit(
			0b11111000 | $5.value,
			BYTE
		);
		emit($3.value, WORD);
	}
	| CMPB '$' VALUE ',' indirect {
		emit(0x80, BYTE);
		emit(
			0b00111000|$5.value,
			BYTE
		);
		emit($3.value, BYTE);
	}
	;

inc:
	INC reg16 {
		emit(0x40+$2.value, BYTE);
	}
	;

xor:
	XOR reg16 ',' reg16 {
		emit(0x31, BYTE);
		emit(
			0b11000000 |
			($2.value << 3) |
			($4.value),
			BYTE
		);
	}
	;

not:
	NOT reg16 {
		emit(0xf7, BYTE);
		emit(
			0b11010000|$2.value,
			BYTE
		);
	}
	;

mov:
	MOV reg16 ',' sreg {
		emit(0x8e, BYTE);
		emit(
			0b11000000 |
			($4.value << 3) |
			($2.value),
			BYTE
		);
	}
	| MOV reg16 ',' reg16 {
		emit(0x89, BYTE);
		emit(
			0b11000000 |
			($2.value << 3) |
			($4.value),
			BYTE
		);
	}
	| MOV '$' VALUE ',' reg16 {
		emit(0xb8+$5.value, BYTE);
		emit($3.value,      WORD);
	}
	| MOV '$' SYMBOL ',' reg16 {
		emit(0xb8+$5.value, BYTE);
		emitGap(MIO_GAP_ABSOLUTE_WORD|MIO_GAP_FLAG_READ, $3.string);
		free($3.string);
	}
	| MOV '$' VALUE ',' reg8 {
		emit(0xb0+$5.value, BYTE);
		emit($3.value,      BYTE);
	}
	| MOV '$' SYMBOL ',' reg8 {
		emit(0xb0+$5.value, BYTE);
		emitGap(MIO_GAP_ABSOLUTE_BYTE|MIO_GAP_FLAG_READ, $3.string);
		free($3.string);
	}
	| MOV reg8 ',' SYMBOL {
		emit(0x88, BYTE);
		emit($2.value<<3|0b110, BYTE); // displacement
		emitGap(MIO_GAP_ABSOLUTE_WORD|MIO_GAP_FLAG_WRITE, $4.string);
		free($4.string);
	}
	| MOV reg8 ',' indirect {
		emit(0x88, BYTE);
		emit($2.value<<3|$4.value, BYTE);
	}
	| MOV SYMBOL ',' reg8 {
		emit(0x8a, BYTE);
		emit($4.value<<3|0b110, BYTE); // displacement
		emitGap(MIO_GAP_ABSOLUTE_WORD|MIO_GAP_FLAG_READ, $2.string);
		free($2.string);
	}
	| MOV indirect ',' reg8 {
		emit(0x8a, BYTE);
		emit($2.value|$4.value<<3, BYTE);
	}
	;

movb:
	MOVB '$' VALUE ',' indirect {
		emit(0xc6, BYTE);
		emit(
			0 | $5.value,
			BYTE
		);
		emit($3.value, BYTE);
	}
	;

push_pop:
	  PUSH reg16 {
		emit(0x50+$2.value, BYTE);
	  }
	| POP reg16 {
		emit(0x58+$2.value, BYTE);
	}
	| PUSH ES {
		emit(0x06, BYTE);
	}
	| POP ES {
		emit(0x07, BYTE);
	}
	| PUSH DS {
		emit(0x1e, BYTE);
	}
	| POP DS {
		emit(0x1f, BYTE);
	}
	| PUSHF {
		emit(0x9c, BYTE);
	}
	| POPF {
		emit(0x9d, BYTE);
	}
	;

indirect:
	  segment_override '(' BX ')' { $$.value = 0b111; }
	| segment_override '(' SI ')' { $$.value = 0b100; }
	| segment_override '(' DI ')' { $$.value = 0b101; }
	;

segment_override:
	| FS ':' {
		if (header.uarch < MIO_UARCH_I386)
		{
			fprintf(stderr, "%s:%d: Warning F segment override promotes to micro-architecture I386\n", filename, $1.lineno);
			header.uarch = MIO_UARCH_I386;
		}
		emit(0x64, BYTE);
	}
	| GS ':' {
		if (header.uarch < MIO_UARCH_I386)
		{
			fprintf(stderr, "%s:%d: Warning G segment override promotes to micro-architecture I386\n", filename, $1.lineno);
			header.uarch = MIO_UARCH_I386;
		}

		emit(0x65, BYTE);
	}
	| ES ':' {
		emit(0x26, BYTE);
	}
	| DS ':' {
		emit(0x3e, BYTE);
	}
	| // no override
	;

data16:
	| {
		if (code != 16)
		{
			emit(0x66, BYTE);
		}
	}
	;

reg16:
	  AX { $$.value = 0b000; }
	| CX { $$.value = 0b001; }
	| DX { $$.value = 0b010; }
	| BX { $$.value = 0b011; }
	| SP { $$.value = 0b100; }
	| BP { $$.value = 0b101; }
	| SI { $$.value = 0b110; }
	| DI { $$.value = 0b111; }
	;

reg8:
	  AL { $$.value = 0b000; }
	| CL { $$.value = 0b001; }
	| DL { $$.value = 0b010; }
	| BL { $$.value = 0b011; }
	| AH { $$.value = 0b100; }
	| CH { $$.value = 0b101; }
	| DH { $$.value = 0b110; }
	| BH { $$.value = 0b111; }
	;

sreg:
	  ES { $$.value = 0b000; }
	| CS { $$.value = 0b001; }
	| SS { $$.value = 0b010; }
	| DS { $$.value = 0b011; }
	| FS { $$.value = 0b100; }
	| GS { $$.value = 0b101; }
	;

%%

void
yyerror (const char *msg)
{
	errors++;
	fprintf(stderr, "%s:%d: %s\n", filename, lineno, msg);
}
