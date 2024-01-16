#include <string.h>
#include <stddef.h>

char *
strncpy (char *restrict dst, const char *restrict src, size_t n)
{
    stpncpy(dst, src, n);
    return dst;
}

char *
stpncpy (char *restrict dst, const char *restrict src, size_t n)
{
#ifdef RESILIENT
    if (!dst || !src)
    {
        return dst;
    }
#endif

    while (*src && n)
    {
        *dst = *src;

        src++;
        dst++;
        n--;
    }

    char *ret = dst;

    while (n)
    {
        *dst = (char)0;
        dst++;
        n--;
    }

    return ret;
}
