#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <string.h>

int
parse_x86_16_singlet (const char *instruction, int opcode)
{
	if (ltok.type != TOK_SYMBOL || strcmp(instruction, ltok.buf))
	{
		return 0;
	}
	lex();

	char op = opcode & 0xff;
	emit(&op, 1);

	return 1;
}
