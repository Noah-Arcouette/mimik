#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_string (void)
{
	if (ltok.type != TOK_SYMBOL) return 0;

	int opcode;

	// movs
	if (!strcmp(ltok.buf, "movs"))
	{
		opcode = 0b10100100;
	}
	// cmps
	else if (!strcmp(ltok.buf, "cmps"))
	{
		opcode = 0b10100110;
	}
	// scas
	else if (!strcmp(ltok.buf, "scas"))
	{
		opcode = 0b10101110;
	}
	// lods
	else if (!strcmp(ltok.buf, "lods"))
	{
		opcode = 0b10101100;
	}
	// stos
	else if (!strcmp(ltok.buf, "stos"))
	{
		opcode = 0b10101010;
	}
	else return 0;

	lex();

	// .byte
	if (ltok.type == TOK_BYTE)
	{
		emit(&opcode, 1);
		lex();
		return 1;
	}
	// .word
	if (ltok.type == TOK_WORD)
	{
		opcode |= 1;
		emit(&opcode, 1);
		lex();
		return 1;
	}

	prettyprint(gettext("Expected .word or .byte\n"));
	recover();
	return 1;
}
