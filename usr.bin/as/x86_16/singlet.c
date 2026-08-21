#include "../main.h"
#include "../emit.h"
#include "x86_16.h"
#include <wchar.h>

int
parse_x86_16_singlet (const wchar_t *instruction, int opcode)
{
	if (ltok.type != TOK_SYMBOL || wcscmp(instruction, ltok.buf))
	{
		return 0;
	}
	lex();

	char op = opcode & 0xff;
	emit(&op, 1);

	return 1;
}
