#include "../parse.h"
#include "x86_16.h"

int
parse_x86_16 (void)
{
	if (parse_x86_16_mov()) return 1;
	if (parse_x86_16_jmp()) return 1;
	if (parse_x86_16_interrupt()) return 1;
	if (parse_x86_16_jcc()) return 1;
	if (parse_x86_16_inc_dec()) return 1;

	// reserves
	if (parse_x86_16_reserve()) return 1;

	// string type
	if (parse_x86_16_string()) return 1;

	// arithmetics
	if (parse_x86_16_arithmetic(
		L"add",
		0b00000000,
		0b10000000, 0b000,
		0b00000100, 1, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"adc",
		0b00010000,
		0b10000000, 0b010,
		0b00010100, 1, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"sub",
		0b00101000,
		0b10000000, 0b101,
		0b00101100, 1, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"ssb",
		0b00011000,
		0b10000000, 0b011,
		0b00001110, 1, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"cmp",
		0b00111000,
		0b10000000, 0b111,
		0b00111100, 1, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"and",
		0b00100000,
		0b10000000, 0b100,
		0b00100100, 0, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"or",
		0b00001000,
		0b10000000, 0b001,
		0b00001100, 0, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"xor",
		0b00110000,
		0b10000000, 0b110,
		0b00110100, 0, 1)) return 1;
	if (parse_x86_16_arithmetic(
		L"test",
		0b10000100,
		0b11110110, 0b000,
		0b10101000, 0, 0)) return 1;

	// singlets
	if (parse_x86_16_singlet(L"ret",  0b11000011)) return 1;
	if (parse_x86_16_singlet(L"clc",  0b11111000)) return 1;
	if (parse_x86_16_singlet(L"cmc",  0b11110101)) return 1;
	if (parse_x86_16_singlet(L"stc",  0b11111001)) return 1;
	if (parse_x86_16_singlet(L"cld",  0b11111100)) return 1;
	if (parse_x86_16_singlet(L"std",  0b11111101)) return 1;
	if (parse_x86_16_singlet(L"cli",  0b11111010)) return 1;
	if (parse_x86_16_singlet(L"sti",  0b11111011)) return 1;
	if (parse_x86_16_singlet(L"hlt",  0b11110100)) return 1;
	if (parse_x86_16_singlet(L"wait", 0b10011011)) return 1;
	if (parse_x86_16_singlet(L"nop",  0b10010000)) return 1;

	// prefixes
	if (parse_x86_16_singlet(L"repnz", 0b11110010)) return 1;
	if (parse_x86_16_singlet(L"repz",  0b11110011)) return 1;
	if (parse_x86_16_singlet(L"es",    0b00100110)) return 1;
	if (parse_x86_16_singlet(L"cs",    0b00101110)) return 1;
	if (parse_x86_16_singlet(L"ss",    0b00110110)) return 1;
	if (parse_x86_16_singlet(L"ds",    0b00111110)) return 1;
	if (parse_x86_16_singlet(L"lock",  0b11110000)) return 1;

	return 0;
}
