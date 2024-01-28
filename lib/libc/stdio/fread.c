#include <stdio.h>
#include <stddef.h>

size_t 
fread (void *restrict buf, size_t itemsz, size_t items, FILE *restrict stream)
{
	for (size_t item = 0; item<items; item++)
	{
		for (size_t i = 0; i<itemsz; i++)
		{
			int val = (unsigned char)fgetc(stream);
			if (val == EOF)
			{
				return item;
			}
			*(unsigned char *)buf = (unsigned char)val;
			buf++;
		}
	}
	return items;
}
