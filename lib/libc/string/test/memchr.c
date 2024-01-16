#include <stdio.h>
#include <string.h>

int
main (void)
{
    int err = 0;
    char *buff = "StringString";
    char *x = memchr(buff, 'S', 12);
    if (!x)
    {
        puts("libc/memchr 12: Does not find first character match");
        err = 1;
    }
    else if (x != buff)
    {
        puts("libc/memchr 17: Mismatches on first character match");
        err = 1;
    }

    x = memchr(buff, (char)0, 13);
    if (!x)
    {
        puts("libc/memchr 24: Does not find last character match");
        err = 1;
    }
    else if (x != buff+12)
    {
        puts("libc/memchr 29: Mismatches on last character match");
        err = 1;
    }

    x = memchr(buff, 'r', 12);
    if (!x)
    {
        puts("libc/memchr 36: Does not find character");
        err = 1;
    }
    else if (x != buff+2)
    {
        puts("libc/memchr 41: Mismatches");
        err = 1;
    }

    x = memchr(buff, '=', 12);
    if (x)
    {
        puts("libc/memchr 48: Matches on nothing");
        err = 1;
    }

    buff = "Hello\0world!";
    x = memchr(buff, '!', 13);
    if (!x)
    {
        puts("libc/memchr 56: Does not find character after 0");
        err = 1;
    }
    else if (x != buff+11)
    {
        puts("libc/memchr 61: Mismatches past 0");
        err = 1;
    }

    if (err)
    {
        puts("libc/memchr:\tInconsistent!");
    }
    else
    {
        puts("libc/memchr:\tConsistent");
    }
    return err;
}
