#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_jmp (void)
{
	if (ltok.type != TOK_SYMBOL) return 0;
	// symbol

	// call
	if (!strcmp(ltok.buf, "call"))
	{
		lex();

		// symbol
		if (ltok.type != TOK_SYMBOL)
		{
			prettyprint(gettext("Expected a symbol\n"));
			errors++;
			recover();
			return 1;
		}

		// emit the data
		char buf = 0b11101000;
		emit(&buf, 1);

		emitGap(ltok.buf, MIO_GAP_TYPE_DISP_LE16|MIO_GAP_TYPE_EXECUTING);

		lex();
		return 1;
	}
	// else

	// jmp
	if (!strcmp(ltok.buf, "jmp"))
	{
		lex();

		int reg;
		struct mem16 addr;

		// symbol
		if (ltok.type == TOK_SYMBOL)
		{
			// emit the data
			char buf = 0b11101001;
			emit(&buf, 1);

			emitGap(ltok.buf, MIO_GAP_TYPE_DISP_LE16|MIO_GAP_TYPE_EXECUTING);

			lex();
			return 1;
		}
		// register
		else if (parse_x86_16_reg16(&reg))
		{
			// indirect jump
			char buf[2] = { 0xff, 0b11100000|reg };
			emit(buf, 2);
			return 1;
		}
		// address
		else if (parse_x86_16_mem16(&addr, MIO_GAP_TYPE_EXECUTING))
		{
			// indirect jump
			char buf[1] = { 0xff };
			emit(buf, 1);
			addr.modrm |= 0b100000;
			emit_x86_16_mem16(&addr);
			free_x86_16_mem16(&addr);
			return 1;
		}
		prettyprint(gettext("Expected a symbol, address, or 16bit register\n"));
		recover();
		return 1;
	}
	// else

	// ljmp
	if (!strcmp(ltok.buf, "ljmp"))
	{
		lex();

		long val;
		struct mem16 addr;

		// symbol
		if (ltok.type == TOK_SYMBOL) // fall through on success
		{
			// emit the data
			char buf = 0b11101010;
			emit(&buf, 1);

			emitGap(ltok.buf, MIO_GAP_TYPE_LIT_LE16|MIO_GAP_TYPE_EXECUTING);

			lex();
			// fall through
		}
		// number
		else if (parse_number(&val)) // fall through on success
		{
			// emit the data
			char buf[3] = { 0b11101010, val&0xff, (val>>8)&0xff };
			emit(buf, 3);
			// fall through
		}
		// address
		else if (parse_x86_16_mem16(&addr, MIO_GAP_TYPE_READING))
		{
			// indirect jump
			char buf[1] = { 0xff };
			emit(buf, 1);
			addr.modrm |= 0b101000;
			emit_x86_16_mem16(&addr);
			free_x86_16_mem16(&addr);
			return 1;
		}
		else
		{
			prettyprint(gettext("Expected a symbol, address, or number\n"));
			recover();
			return 1;
		}

		// number or symbol
		// now again, number or symbol

		// symbol
		if (ltok.type == TOK_SYMBOL) // fall through on success
		{
			emitGap(ltok.buf, MIO_GAP_TYPE_LIT_LE16|MIO_GAP_TYPE_EXECUTING);

			lex();
			return 1;
		}
		// number
		if (parse_number(&val)) // fall through on success
		{
			// emit the data
			char buf[2] = { val&0xff, (val>>8)&0xff };
			emit(buf, 2);
			return 1;
		}
		prettyprint(gettext("Expected a symbol or number\n"));
		recover();
		return 1;
	}
	// else

	// sjmp
	if (!strcmp(ltok.buf, "sjmp"))
	{
		lex();

		// symbol
		if (ltok.type != TOK_SYMBOL)
		{
			prettyprint(gettext("Expected a symbol\n"));
			errors++;
			recover();
			return 1;
		}

		// emit the data
		char buf = 0b11101011;
		emit(&buf, 1);

		emitGap(ltok.buf, MIO_GAP_TYPE_DISP_BYTE|MIO_GAP_TYPE_EXECUTING);

		lex();
		return 1;
	}
	// else

	return 0;
}
