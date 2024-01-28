#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;

    const char *buff = "StringString";
    char *x = strpbrk(buff, "tr");
    if (!x)
    {
        puts("libc/strpbrk 13: Cannot find match");
        err = 1;
    }
    else if (x != buff+1)
    {
        puts("libc/strpbrk 18: Finds wrong match");
        err = 1;
    }

    x = strpbrk(buff, "lw");
    if (x)
    {
        puts("libc/strpbrk 25: Mismatches");
        err = 1;
    }

    x = strpbrk("", "String");
    if (x)
    {
        puts("libc/strpbrk 32: Matches on nothing");
        err = 1;
    }

    x = strpbrk(buff, "");
    if (x)
    {
        puts("libc/strpbrk 39: Matches nothing");
        err = 1;
    }

    if (err)
    {
        puts("libc/strpbrk:\tInconsistent!");
    }
    else
    {
        puts("libc/strpbrk:\tConsistent");
    }
    return err;
}
