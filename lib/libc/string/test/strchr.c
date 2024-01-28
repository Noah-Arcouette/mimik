#include <stdio.h>
#include <string.h>

int
main (void)
{
    int err = 0;
    char *buff = "StringString";
    char *x = strchr(buff, 'S');
    if (!x)
    {
        puts("libc/strchr 12: Does not find first character match");
        err = 1;
    }
    else if (x != buff)
    {
        puts("libc/strchr 17: Mismatches on first character match");
        err = 1;
    }

    x = strchr(buff, (char)0);
    if (!x)
    {
        puts("libc/strchr 24: Does not find last character match");
        err = 1;
    }
    else if (x != buff+12)
    {
        puts("libc/strchr 29: Mismatches on last character match");
        err = 1;
    }

    x = strchr(buff, 'r');
    if (!x)
    {
        puts("libc/strchr 36: Does not find character");
        err = 1;
    }
    else if (x != buff+2)
    {
        puts("libc/strchr 41: Mismatches");
        err = 1;
    }

    x = strchr(buff, '=');
    if (x)
    {
        puts("libc/strchr 48: Matches on nothing");
        err = 1;
    }

    if (err)
    {
        puts("libc/strchr:\tInconsistent!");
    }
    else
    {
        puts("libc/strchr:\tConsistent");
    }
    return err;
}
