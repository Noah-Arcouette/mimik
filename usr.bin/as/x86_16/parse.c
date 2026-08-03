#include "../parse.h"
#include "x86_16.h"

int
parse_x86_16 (void)
{
	if (parse_x86_16_jmp()) return 1;

	if (parse_x86_16_arithmetic(
		"add",
		0b00000000,
		0b10000000, 0b000,
		0b00000100, 1)) return 1;
	if (parse_x86_16_arithmetic(
		"adc",
		0b00010000,
		0b10000000, 0b010,
		0b00010100, 1)) return 1;
	if (parse_x86_16_arithmetic(
		"sub",
		0b00101000,
		0b10000000, 0b101,
		0b00101100, 1)) return 1;
	if (parse_x86_16_arithmetic(
		"sub",
		0b00011000,
		0b10000000, 0b011,
		0b00001110, 1)) return 1;
	if (parse_x86_16_arithmetic(
		"cmp",
		0b00111000,
		0b10000000, 0b111,
		0b00111100, 1)) return 1;
	if (parse_x86_16_arithmetic(
		"and",
		0b00100000,
		0b10000000, 0b100,
		0b00100100, 0)) return 1;
	if (parse_x86_16_arithmetic(
		"or",
		0b00001000,
		0b10000000, 0b001,
		0b00001100, 0)) return 1;
	if (parse_x86_16_arithmetic(
		"xor",
		0b00110000,
		0b10000000, 0b110,
		0b00110100, 0)) return 1;

	if (parse_x86_16_singlet("cli", 0b11111010)) return 1;
	if (parse_x86_16_singlet("hlt", 0b11110100)) return 1;
	if (parse_x86_16_singlet("nop", 0b10010000)) return 1;

	return 0;
}
