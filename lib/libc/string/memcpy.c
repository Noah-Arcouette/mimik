#include <string.h>

void *
memcpy (void *restrict dst, const void *restrict src, size_t n)
{
#ifdef RESILIENT
    if (!dst || !src)
    {
        return dst;
    }
#endif
    void *r = dst;
    while (n--)
        *(unsigned char *)dst++ = *(unsigned char *)src++;

    return r;
}
