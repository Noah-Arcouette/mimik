#include "../main.h"
#include "x86_16.h"
#include <string.h>

int
parse_x86_16_reg16 (int *reg)
{
	if (ltok.type != TOK_REGISTER)
	{
		return 0;
	}

	switch (ltok.buf[1])
	{
	case L'a':
		if (!wcscmp(ltok.buf+2, L"x"))
		{
			lex();
			if (reg) *reg = 0b000;
			return 1;
		}
		return 0;
	case L'b':
		if (!wcscmp(ltok.buf+2, L"x"))
		{
			lex();
			if (reg) *reg = 0b011;
			return 1;
		}
		if (!wcscmp(ltok.buf+2, L"p"))
		{
			lex();
			if (reg) *reg = 0b101;
			return 1;
		}
		return 0;
	case L'c':
		if (!wcscmp(ltok.buf+2, L"x"))
		{
			lex();
			if (reg) *reg = 0b001;
			return 1;
		}
		return 0;
	case L'd':
		if (!wcscmp(ltok.buf+2, L"x"))
		{
			lex();
			if (reg) *reg = 0b010;
			return 1;
		}
		if (!wcscmp(ltok.buf+2, L"i"))
		{
			lex();
			if (reg) *reg = 0b111;
			return 1;
		}
		return 0;
	case L's':
		if (!wcscmp(ltok.buf+2, L"p"))
		{
			lex();
			if (reg) *reg = 0b100;
			return 1;
		}
		if (!wcscmp(ltok.buf+2, L"i"))
		{
			lex();
			if (reg) *reg = 0b110;
			return 1;
		}
		return 0;
	}

	return 0;
}
