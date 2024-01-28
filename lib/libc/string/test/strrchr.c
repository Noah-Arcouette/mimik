#include <stdio.h>
#include <string.h>

int
main (void)
{
    int err = 0;
    char *buff = "StringString";
    char *x = strrchr(buff, 'S');
    if (!x)
    {
        puts("libc/strrchr 12: Does not find first character match");
        err = 1;
    }
    else if (x != buff+6)
    {
        puts("libc/strrchr 17: Mismatches on first character match");
        err = 1;
    }

    x = strrchr(buff, (char)0);
    if (!x)
    {
        puts("libc/strrchr 24: Does not find last character match");
        err = 1;
    }
    else if (x != buff+12)
    {
        puts("libc/strrchr 29: Mismatches on last character match");
        err = 1;
    }

    x = strrchr(buff, 'r');
    if (!x)
    {
        puts("libc/strrchr 36: Does not find character");
        err = 1;
    }
    else if (x != buff+8)
    {
        puts("libc/strrchr 41: Mismatches");
        err = 1;
    }

    x = strrchr(buff, '=');
    if (x)
    {
        puts("libc/strrchr 48: Matches on nothing");
        err = 1;
    }

    if (err)
    {
        puts("libc/strrchr:\tInconsistent!");
    }
    else
    {
        puts("libc/strrchr:\tConsistent");
    }
    return err;
}
