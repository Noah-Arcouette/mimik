#include "../main.h"
#include "x86_16.h"
#include <string.h>

int
parse_x86_16_sreg (int *reg)
{
	if (ltok.type != TOK_REGISTER)
	{
		return 0;
	}

	switch (ltok.buf[1])
	{
	case 'e':
		if (!strcmp(ltok.buf+2, "s"))
		{
			lex();
			if (reg) *reg = 0b000;
			return 1;
		}
		return 0;
	case 'c':
		if (!strcmp(ltok.buf+2, "s"))
		{
			lex();
			if (reg) *reg = 0b001;
			return 1;
		}
		return 0;
	case 'd':
		if (!strcmp(ltok.buf+2, "s"))
		{
			lex();
			if (reg) *reg = 0b011;
			return 1;
		}
		return 0;
	case 's':
		if (!strcmp(ltok.buf+2, "s"))
		{
			lex();
			if (reg) *reg = 0b010;
			return 1;
		}
		return 0;
	}

	return 0;
}
