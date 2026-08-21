#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_mov (void)
{
	if (ltok.type != TOK_SYMBOL || wcscmp(ltok.buf, L"mov")) return 0;
	lex();

	int regA;
	int regB;
	struct mem16 addr;
	long val;

	// reg16
	if (parse_x86_16_reg16(&regA))
	{
		// mem
		if (parse_x86_16_mem16(&addr, MIO_GAP_TYPE_READING))
		{
			// check for mov ax [val]
			if (regA == 0 && addr.modrm == 0b00000110)
			{
				char buf[1] = { 0b10100001 };
				emit(buf, 1);
				if (addr.symbol)
				{
					emitGap(addr.symbol, addr.gapType);
				}
				else
				{
					emit(addr.displacement, 2);
				}
			}
			else
			{
				char buf[1] = { 0b10001011 };
				emit(buf, 1);
				addr.modrm |= regA<<3;
				emit_x86_16_mem16(&addr);
			}
			free_x86_16_mem16(&addr);
			return 1;
		}
		// reg16
		if (parse_x86_16_reg16(&regB))
		{
			char buf[2] = { 0b10001011, 0b11000000|regA<<3|regB };
			emit(buf, 2);
			return 1;
		}
		// number (imm16)
		if (parse_number(&val))
		{
			char buf[3] = { 0b10111000|regA, val&0xff, (val>>8)&0xff };
			emit(buf, 3);
			return 1;
		}
		// symbol (imm16)
		if (ltok.type == TOK_SYMBOL)
		{
			char buf[1] = { 0b10111000|regA };
			emit(buf, 1);
			emitGap(ltok.buf, MIO_GAP_TYPE_LIT_LE16);
			lex();
			return 1;
		}
		// sreg
		if (parse_x86_16_sreg(&regB))
		{
			char buf[2] = { 0b10001100, 0b11000000|regB<<3|regA };
			emit(buf, 2);
			return 1;
		}

		prettyprint(gettext("Expected a memory address, 16bit register, \
number, symbols, or segment register\n"));
		recover();
		errors++;
		return 1;
	}

	// reg8
	if (parse_x86_16_reg8(&regA))
	{
		// mem
		if (parse_x86_16_mem16(&addr, MIO_GAP_TYPE_READING))
		{
			// check for mov al [val]
			if (regA == 0 && addr.modrm == 0b00000110)
			{
				char buf[1] = { 0b10100000 };
				emit(buf, 1);
				if (addr.symbol)
				{
					emitGap(addr.symbol, addr.gapType);
				}
				else
				{
					emit(addr.displacement, 2);
				}
			}
			else
			{
				char buf[1] = { 0b10001010 };
				emit(buf, 1);
				addr.modrm |= regA<<3;
				emit_x86_16_mem16(&addr);
			}
			free_x86_16_mem16(&addr);
			return 1;
		}
		// reg8
		if (parse_x86_16_reg8(&regB))
		{
			char buf[2] = { 0b10001010, 0b11000000|regA<<3|regB };
			emit(buf, 2);
			return 1;
		}
		// number (imm8)
		if (parse_number(&val))
		{
			char buf[2] = { 0b10110000|regA, val&0xff };
			emit(buf, 2);
			return 1;
		}
		// symbol (imm8)
		if (ltok.type == TOK_SYMBOL)
		{
			char buf[1] = { 0b10110000|regA };
			emit(buf, 1);
			emitGap(ltok.buf, MIO_GAP_TYPE_LIT_BYTE);
			lex();
			return 1;
		}

		prettyprint(gettext("Expected a memory address, 16bit register, \
number, symbols\n"));
		recover();
		errors++;
		return 1;
	}

	// mem
	if (parse_x86_16_mem16(&addr, MIO_GAP_TYPE_WRITING))
	{
		// reg16
		if (parse_x86_16_reg16(&regA))
		{
			// check for mov ax [val]
			if (regA == 0 && addr.modrm == 0b00000110)
			{
				char buf[1] = { 0b10100011 };
				emit(buf, 1);
				if (addr.symbol)
				{
					emitGap(addr.symbol, addr.gapType);
				}
				else
				{
					emit(addr.displacement, 2);
				}
			}
			else
			{
				char buf[1] = { 0b10001001 };
				emit(buf, 1);
				addr.modrm |= regA<<3;
				emit_x86_16_mem16(&addr);
			}
			free_x86_16_mem16(&addr);
			return 1;
		}
		// reg8
		if (parse_x86_16_reg8(&regA))
		{
			// check for mov ax [val]
			if (regA == 0 && addr.modrm == 0b00000110)
			{
				char buf[1] = { 0b10100010 };
				emit(buf, 1);
				if (addr.symbol)
				{
					emitGap(addr.symbol, addr.gapType);
				}
				else
				{
					emit(addr.displacement, 2);
				}
			}
			else
			{
				char buf[1] = { 0b10001000 };
				emit(buf, 1);
				addr.modrm |= regA<<3;
				emit_x86_16_mem16(&addr);
			}
			free_x86_16_mem16(&addr);
			return 1;
		}
		// sreg
		if (parse_x86_16_sreg(&regA))
		{
			addr.modrm |= regA<<3;

			char buf[1] = { 0b10001100 };
			emit(buf, 1);
			emit_x86_16_mem16(&addr);
			free_x86_16_mem16(&addr);
			return 1;
		}

		prettyprint(gettext("Expected a 16bit register, an 8bit register, \
or segment register\n"));
		recover();
		errors++;
		return 1;
	}

	// sreg
	if (parse_x86_16_sreg(&regA))
	{
		// mem
		if (parse_x86_16_mem16(&addr, MIO_GAP_TYPE_READING))
		{
			char buf[1] = { 0b10001110 };
			emit(buf, 1);
			addr.modrm |= regA<<3;
			emit_x86_16_mem16(&addr);
			free_x86_16_mem16(&addr);
			return 1;
		}
		// reg16
		if (parse_x86_16_reg16(&regB))
		{
			char buf[2] = { 0b10001110, 0b11000000|regA<<3|regB };
			emit(buf, 2);
			return 1;
		}

		prettyprint(
			gettext("Expected a 16bit register, or a memory address\n"));
		recover();
		errors++;
		return 1;
	}

	// .byte mem imm8
	if (ltok.type == TOK_BYTE)
	{
		lex();

		if (!parse_x86_16_mem16(&addr, MIO_GAP_TYPE_WRITING))
		{
			prettyprint(gettext("Expected a memory address\n"));
			errors++;
			recover();
			return 1;
		}

		char buf[1] = { 0b11000110 };
		emit(buf, 1);
		emit_x86_16_mem16(&addr);
		free_x86_16_mem16(&addr);

		if (parse_number(&val))
		{
			char buf2[1] = { val&0xff };
			emit(buf2, 1);
		}
		else if (ltok.type == TOK_SYMBOL)
		{
			emitGap(ltok.buf, MIO_GAP_TYPE_LIT_BYTE);
			lex();
		}
		else
		{
			prettyprint(gettext("Expected a number or symbol\n"));
			errors++;
			recover();
		}
		return 1;
	}
	// .word mem imm16
	if (ltok.type == TOK_WORD)
	{
		lex();

		if (!parse_x86_16_mem16(&addr, MIO_GAP_TYPE_WRITING))
		{
			prettyprint(gettext("Expected a memory address\n"));
			errors++;
			recover();
			return 1;
		}

		char buf[1] = { 0b11000111 };
		emit(buf, 1);
		emit_x86_16_mem16(&addr);
		free_x86_16_mem16(&addr);

		if (parse_number(&val))
		{
			char buf2[2] = { val&0xff, (val>>8)&0xff };
			emit(buf2, 2);
		}
		else if (ltok.type == TOK_SYMBOL)
		{
			emitGap(ltok.buf, MIO_GAP_TYPE_LIT_LE16);
			lex();
		}
		else
		{
			prettyprint(gettext("Expected a number or symbol\n"));
			errors++;
			recover();
		}
		return 1;
	}

	prettyprint(gettext("Expected a register or a memory address\n"));
	recover();
	errors++;
	return 1;
}
