#include <stdio.h>
#include <string.h>

int
fputs (const char *restrict s, FILE *restrict stream)
{
    if (fwrite(s, sizeof(char), strlen(s), stream) != strlen(s))
    {
        return EOF;
    }
    return 0;
}

int
puts (const char *s)
{
    if (fwrite(s, sizeof(char), strlen(s), stdout) != strlen(s))
    {
        return EOF;
    }
    return fwrite("\n", sizeof(char), 1, stdout);
}
