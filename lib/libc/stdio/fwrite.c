#include "stdio.h"
#include <stddef.h>

size_t 
fwrite (const void *restrict buf, size_t itemsz, size_t items, FILE *restrict stream)
{
    for (size_t item = 0; item<items; item++)
    {
        for (size_t i = 0; i<itemsz; i++)
        {
            if (fputc(*(unsigned char *)buf, stream) == EOF)
            {
                return item;
            }
            buf++;
        }
    }
    return items;
}
