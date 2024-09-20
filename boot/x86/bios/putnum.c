#include "colors.h"
#include "lang.h"
#include "unreal.h"

void
putnum (unsigned int number, unsigned int base, unsigned char color)
{
	if (base > ALPHA_MAX_BASE)
	{
		puts(BASE_RANGE_ERROR, FG_RED);
	}

	unsigned int rem = number%base;
	unsigned int val = number/base;

	if (val)
	{
		putnum(val, base, color);
	}

	putc(ALPHA[rem], color);
}
