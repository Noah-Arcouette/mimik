#include <string.h>
#include <stddef.h>

void *
memset (void *s, int c, size_t n)
{
#ifdef RESILIENT
    if (!s)
    {
        return s;
    }
#endif

    while (n--)
    {
        ((unsigned char *)s)[n] = (unsigned char)c;
    }
    return s;
}
