#include <string.h>

char *
strchr (const char *s, int c)
{
#ifdef RESILIENT
    if (!s)
    {
        return (char*)s;
    }
#endif

    do
    {
        if (*s == (char)c)
        {
            return (char *)s;
        }
    } while (*s++);

    return (char*)NULL;
}

char *
strrchr (const char *s, int c)
{
#ifdef RESILIENT
    if (!s)
    {
        return (char*)s;
    }
#endif

    char *found = (char*)NULL;
    do
    {
        if (*s == (char)c)
        {
            found = (char *)s;
        }
    } while (*s++);

    return found;
}
