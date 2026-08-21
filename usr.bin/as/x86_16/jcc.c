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
	if (ltok.buf[0] == L'j')
	{
		if (!wcscmp(ltok.buf, L"je"))
		{
			opcode = 0b01110100;
		}
		else if (!wcscmp(ltok.buf, L"jz"))
		{
			opcode = 0b01110100;
		}
		else if (!wcscmp(ltok.buf, L"jl"))
		{
			opcode = 0b01111100;
		}
		else if (!wcscmp(ltok.buf, L"jnge"))
		{
			opcode = 0b01111100;
		}
		else if (!wcscmp(ltok.buf, L"jle"))
		{
			opcode = 0b01111110;
		}
		else if (!wcscmp(ltok.buf, L"jng"))
		{
			opcode = 0b01111110;
		}
		else if (!wcscmp(ltok.buf, L"jb"))
		{
			opcode = 0b01110010;
		}
		else if (!wcscmp(ltok.buf, L"jc"))
		{
			opcode = 0b01110010;
		}
		else if (!wcscmp(ltok.buf, L"jnae"))
		{
			opcode = 0b01110010;
		}
		else if (!wcscmp(ltok.buf, L"jbe"))
		{
			opcode = 0b01110110;
		}
		else if (!wcscmp(ltok.buf, L"jna"))
		{
			opcode = 0b01110110;
		}
		else if (!wcscmp(ltok.buf, L"jp"))
		{
			opcode = 0b01111010;
		}
		else if (!wcscmp(ltok.buf, L"jpe"))
		{
			opcode = 0b01111010;
		}
		else if (!wcscmp(ltok.buf, L"jo"))
		{
			opcode = 0b01110000;
		}
		else if (!wcscmp(ltok.buf, L"js"))
		{
			opcode = 0b01111000;
		}
		else if (!wcscmp(ltok.buf, L"jne"))
		{
			opcode = 0b01110101;
		}
		else if (!wcscmp(ltok.buf, L"jnz"))
		{
			opcode = 0b01110101;
		}
		else if (!wcscmp(ltok.buf, L"jnl"))
		{
			opcode = 0b01111101;
		}
		else if (!wcscmp(ltok.buf, L"jge"))
		{
			opcode = 0b01111101;
		}
		else if (!wcscmp(ltok.buf, L"jnle"))
		{
			opcode = 0b01111111;
		}
		else if (!wcscmp(ltok.buf, L"jg"))
		{
			opcode = 0b01111111;
		}
		else if (!wcscmp(ltok.buf, L"jnb"))
		{
			opcode = 0b01110011;
		}
		else if (!wcscmp(ltok.buf, L"jnc"))
		{
			opcode = 0b01110011;
		}
		else if (!wcscmp(ltok.buf, L"jae"))
		{
			opcode = 0b01110011;
		}
		else if (!wcscmp(ltok.buf, L"jnbe"))
		{
			opcode = 0b01110111;
		}
		else if (!wcscmp(ltok.buf, L"ja"))
		{
			opcode = 0b01110111;
		}
		else if (!wcscmp(ltok.buf, L"jnp"))
		{
			opcode = 0b01111011;
		}
		else if (!wcscmp(ltok.buf, L"jpo"))
		{
			opcode = 0b01111011;
		}
		else if (!wcscmp(ltok.buf, L"jno"))
		{
			opcode = 0b01110001;
		}
		else if (!wcscmp(ltok.buf, L"jns"))
		{
			opcode = 0b01111001;
		}
		else if (!wcscmp(ltok.buf, L"jcxz"))
		{
			opcode = 0b01110011;
		}
		else return 0;
	}
	else if (ltok.buf[0] == L'l')
	{
		if (!wcscmp(ltok.buf, L"loop"))
		{
			opcode = 0b11100010;
		}
		else if (!wcscmp(ltok.buf, L"loopz"))
		{
			opcode = 0b11100001;
		}
		else if (!wcscmp(ltok.buf, L"loope"))
		{
			opcode = 0b11100001;
		}
		else if (!wcscmp(ltok.buf, L"loopnz"))
		{
			opcode = 0b11100000;
		}
		else if (!wcscmp(ltok.buf, L"loopne"))
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
