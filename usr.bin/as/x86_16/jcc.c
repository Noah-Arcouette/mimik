#include "../emit.h"
#include "../main.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_jcc (void)
{
	if (ltok.type != TOK_SYMBOL) return 0;

	char opcode;
	// check for the types
	if (ltok.buf[0] == 'j')
	{
		if (!strcmp(ltok.buf, "je"))
		{
			opcode = 0b01110100;
		}
		else if (!strcmp(ltok.buf, "jz"))
		{
			opcode = 0b01110100;
		}
		else if (!strcmp(ltok.buf, "jl"))
		{
			opcode = 0b01111100;
		}
		else if (!strcmp(ltok.buf, "jnge"))
		{
			opcode = 0b01111100;
		}
		else if (!strcmp(ltok.buf, "jle"))
		{
			opcode = 0b01111110;
		}
		else if (!strcmp(ltok.buf, "jng"))
		{
			opcode = 0b01111110;
		}
		else if (!strcmp(ltok.buf, "jb"))
		{
			opcode = 0b01110010;
		}
		else if (!strcmp(ltok.buf, "jnae"))
		{
			opcode = 0b01110010;
		}
		else if (!strcmp(ltok.buf, "jbe"))
		{
			opcode = 0b01110110;
		}
		else if (!strcmp(ltok.buf, "jna"))
		{
			opcode = 0b01110110;
		}
		else if (!strcmp(ltok.buf, "jp"))
		{
			opcode = 0b01111010;
		}
		else if (!strcmp(ltok.buf, "jpe"))
		{
			opcode = 0b01111010;
		}
		else if (!strcmp(ltok.buf, "jo"))
		{
			opcode = 0b01110000;
		}
		else if (!strcmp(ltok.buf, "js"))
		{
			opcode = 0b01111000;
		}
		else if (!strcmp(ltok.buf, "jne"))
		{
			opcode = 0b01110101;
		}
		else if (!strcmp(ltok.buf, "jnz"))
		{
			opcode = 0b01110101;
		}
		else if (!strcmp(ltok.buf, "jnl"))
		{
			opcode = 0b01111101;
		}
		else if (!strcmp(ltok.buf, "jge"))
		{
			opcode = 0b01111101;
		}
		else if (!strcmp(ltok.buf, "jnle"))
		{
			opcode = 0b01111111;
		}
		else if (!strcmp(ltok.buf, "jg"))
		{
			opcode = 0b01111111;
		}
		else if (!strcmp(ltok.buf, "jnb"))
		{
			opcode = 0b01110011;
		}
		else if (!strcmp(ltok.buf, "jae"))
		{
			opcode = 0b01110011;
		}
		else if (!strcmp(ltok.buf, "jnbe"))
		{
			opcode = 0b01110111;
		}
		else if (!strcmp(ltok.buf, "ja"))
		{
			opcode = 0b01110111;
		}
		else if (!strcmp(ltok.buf, "jnp"))
		{
			opcode = 0b01111011;
		}
		else if (!strcmp(ltok.buf, "jpo"))
		{
			opcode = 0b01111011;
		}
		else if (!strcmp(ltok.buf, "jno"))
		{
			opcode = 0b01110001;
		}
		else if (!strcmp(ltok.buf, "jns"))
		{
			opcode = 0b01111001;
		}
		else if (!strcmp(ltok.buf, "jcxz"))
		{
			opcode = 0b01110011;
		}
		else return 0;
	}
	else if (ltok.buf[0] == 'l')
	{
		if (!strcmp(ltok.buf, "loop"))
		{
			opcode = 0b11100010;
		}
		else if (!strcmp(ltok.buf, "loopz"))
		{
			opcode = 0b11100001;
		}
		else if (!strcmp(ltok.buf, "loope"))
		{
			opcode = 0b11100001;
		}
		else if (!strcmp(ltok.buf, "loopnz"))
		{
			opcode = 0b11100000;
		}
		else if (!strcmp(ltok.buf, "loopne"))
		{
			opcode = 0b11100000;
		}
		else return 0;
	}
	else return 0;
	lex();

	// symbol
	if (ltok.type != TOK_SYMBOL)
	{
		prettyprint(gettext("Expected a symbol\n"));
		recover();
		errors++;
		return 1;
	}

	emit(&opcode, 1);
	emitGap(ltok.buf, MIO_GAP_TYPE_EXECUTING|MIO_GAP_TYPE_DISP_BYTE);
	lex();

	return 1;
}
