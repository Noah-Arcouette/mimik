#include <string.h>
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;

    const char *buff = "StringString";
    char *x = strpbrk(buff, "tr");
    if (!x)
    {
        TITLE();
        puts("Cannot find match");
        err = 1;
    }
    else if (x != buff+1)
    {
        TITLE();
        puts("Finds wrong match");
        err = 1;
    }

    x = strpbrk(buff, "lw");
    if (x)
    {
        TITLE();
        puts("Mismatches");
        err = 1;
    }

    x = strpbrk("", "String");
    if (x)
    {
        TITLE();
        puts("Matches on nothing");
        err = 1;
    }

    x = strpbrk(buff, "");
    if (x)
    {
        TITLE();
        puts("Matches nothing");
        err = 1;
    }

    if (err)
    {
        TITLE();
        puts("\tInconsistent!");
    }
    else
    {
        TITLE();
        puts("\tConsistent");
    }
    return err;
}
