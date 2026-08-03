#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_arithmetic (const char *mnemonic, int opcode, int immOpcode,
	int immCommand, int accOpcode, int _signed)
{
	// op
	if (ltok.type != TOK_SYMBOL || strcmp(ltok.buf, mnemonic)) return 0;
	lex();

	int reg;
	struct mem16 mem;

	// reg8
	if (parse_x86_16_reg8(&reg))
	{
		int regb;
		long val;

		// reg8
		if (parse_x86_16_reg8(&regb))
		{
			char inst[2] = { opcode, 0b11000000|(reg<<3)|regb };
			emit(inst, 2);
		}
		// number
		else if (parse_number(&val))
		{
			if (reg == 0)
			{
				char inst[2] = { accOpcode, val&0xff };
				emit(inst, 2);
			}
			else
			{
				char inst[3] = { immOpcode, 0b11000000|(immCommand<<3)|reg,
					val&0xff };
				emit(inst, 3);
			}
		}
		// symbol
		else if (ltok.type == TOK_SYMBOL)
		{
			if (reg == 0)
			{
				char inst[1] = { accOpcode };
				emit(inst, 1);
				emitGap(ltok.buf, MIO_GAP_TYPE_LIT_BYTE);
			}
			else
			{
				char inst[2] = { immOpcode, 0b11000000|(immCommand<<3)|reg };
				emit(inst, 2);
				emitGap(ltok.buf, MIO_GAP_TYPE_LIT_BYTE);
			}
			lex();
		}
		// mem
		else if (parse_x86_16_mem16(&mem, MIO_GAP_TYPE_READING))
		{
			char inst[1] = { opcode|1 };
			emit(inst, 1);
			mem.modrm |= reg<<3;
			emit_x86_16_mem16(&mem);
			free_x86_16_mem16(&mem);
		}
		else
		{
			prettyprint(gettext(
				"Expected 8bit register, memory address, or an immediate\n"));
			errors++;
			recover();
		}
	}
	// reg16
	else if (parse_x86_16_reg16(&reg))
	{
		int regb;
		long val;

		// reg8
		if (parse_x86_16_reg16(&regb))
		{
			char inst[2] = { opcode|1, 0b11000000|(reg<<3)|regb };
			emit(inst, 2);
		}
		// number
		else if (parse_number(&val))
		{
			if (reg == 0)
			{
				char inst[3] = { accOpcode|1, val&0xff, (val>>8)&0xff };
				emit(inst, 3);
			}
			else
			{
				if (_signed && (val&0xff80) == 0xff80) // sign extended
				{
					char inst[4] = { immOpcode|1, 0b11000000|(immCommand<<3)|reg,
						val&0xff };
					emit(inst, 3);
				}
				else
				{
					char inst[4] = { immOpcode|1, 0b11000000|(immCommand<<3)|reg,
						val&0xff, (val>>8)&0xff };
					emit(inst, 4);
				}
			}
		}
		// symbol
		else if (ltok.type == TOK_SYMBOL)
		{
			if (reg == 0)
			{
				char inst[1] = { accOpcode|1 };
				emit(inst, 1);
				emitGap(ltok.buf, MIO_GAP_TYPE_LIT_LE16);
			}
			else
			{
				char inst[2] = { immOpcode|1, 0b11000000|(immCommand<<3)|reg };
				emit(inst, 2);
				emitGap(ltok.buf, MIO_GAP_TYPE_LIT_LE16);
			}
			lex();
		}
		// mem
		else if (parse_x86_16_mem16(&mem, MIO_GAP_TYPE_READING))
		{
			char inst[1] = { opcode|3 };
			emit(inst, 1);
			mem.modrm |= reg<<3;
			emit_x86_16_mem16(&mem);
			free_x86_16_mem16(&mem);
		}
		else
		{
			prettyprint(gettext(
				"Expected 8bit register, memory address, or an immediate\n"));
			errors++;
			recover();
		}
	}
	// mem
	if (parse_x86_16_mem16(&mem, MIO_GAP_TYPE_WRITING))
	{
		// reg16
		if (parse_x86_16_reg16(&reg))
		{
			char inst[1] = { opcode|1 };
			emit(inst, 1);
			mem.modrm |= reg<<3;
			emit_x86_16_mem16(&mem);
			free_x86_16_mem16(&mem);
		}
		// reg8
		else if (parse_x86_16_reg8(&reg))
		{
			char inst[1] = { opcode };
			emit(inst, 1);
			mem.modrm |= reg<<3;
			emit_x86_16_mem16(&mem);
			free_x86_16_mem16(&mem);
		}
		// number
		// symbol
		else if (ltok.type == TOK_SYMBOL || ltok.type == TOK_NUMBER)
		{
			prettyprint(gettext(
				"Ambiguous memory size, are you missing .byte or .word?\n"));
			errors++;
			lex();
		}
		else
		{
			prettyprint(gettext("Expected 8bit or 16bit register\n"));
			errors++;
			recover();
		}
	}
	/// @todo .byte mem imm8
	/// @todo .word mem imm16

	return 0;
}
