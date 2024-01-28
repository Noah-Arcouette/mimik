#include <string.h>

void *
memccpy (void *restrict dst, const void *restrict src, int c, size_t n)
{
    while (n--)
    {
        *(unsigned char*)dst = *(unsigned char*)src++;

        if (*(unsigned char *)dst++ == (unsigned char)c)
        {
            return dst;
        }
    }
    return (void*)NULL;
}
