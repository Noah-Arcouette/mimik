#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>

int
parse_x86_16_inc_dec (void)
{
	if (ltok.type != TOK_SYMBOL) return 0;

	int command;
	int opcode;
	if (!strcmp(ltok.buf, "inc"))
	{
		command = 0b000000;
		opcode  = 0b01000000;
	}
	else if (!strcmp(ltok.buf, "dec"))
	{
		command = 0b001000;
		opcode  = 0b01001000;
	}
	else return 0;
	lex();

	int reg;
	struct mem16 mem;

	// .byte mem
	if (ltok.type == TOK_BYTE)
	{
		lex();
	_mem:
		if (!parse_x86_16_mem16(&mem,
			MIO_GAP_TYPE_READING|MIO_GAP_TYPE_WRITING))
		{
			prettyprint(gettext("Expected memory address\n"));
			errors++;
			recover();
			return 1;
		}

		char buf[1] = { opcode };
		emit(buf, 1);
		mem.modrm |= command;
		emit_x86_16_mem16(&mem);
		free_x86_16_mem16(&mem);
		return 1;
	}
	// .word mem
	if (ltok.type == TOK_WORD)
	{
		lex();
		opcode |= 1; // wide
		goto _mem;
	}
	// reg8
	if (parse_x86_16_reg8(&reg))
	{
		char buf[2] = { 0xfe, 0b11000000|command|reg };
		emit(buf, 2);
		return 1;
	}
	// reg16
	if (parse_x86_16_reg16(&reg))
	{
		char buf[1] = { opcode|reg };
		emit(buf, 1);
		return 1;
	}

	prettyprint(gettext("Expected .byte, .word, or a register\n"));
	errors++;
	recover();
	return 1;
}
