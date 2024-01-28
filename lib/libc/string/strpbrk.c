#include <string.h>
#include <stddef.h>

char *
strpbrk (const char *s1, const char *s2)
{
#ifdef RESILIENT
    if (!s1 || !s2)
    {
        return (char*)NULL;
    }
#endif

    while (*s1)
    {
        for (size_t i = 0; s2[i]; i++)
        {
            if (*s1 == s2[i])
            {
                return (char*)s1;
            }
        }
        s1++;
    }

    return (char*)NULL;
}
