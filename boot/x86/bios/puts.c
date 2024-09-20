#include "unreal.h"

void
puts (const char *str, char color)
{
	while (*str)
	{
		putc(*str++, color);
	}
}
