#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[256] = "";
    char *x = strcat(buff, "String");

    if (strcmp(buff, "String"))
    {
        puts("libc/strcat 13: Does not concatenate on empty s1");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strcat 18: Does not return s1 on empty s1");
        err = 1;
    }

    x = strcat(buff, "2");
    if (strcmp(buff, "String2"))
    {
        puts("libc/strcat 25: Does not concatenate");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strcat 30: Does not return s1");
        err = 1;
    }

    x = strcat(buff, "");
    if (strcmp(buff, "String2"))
    {
        puts("libc/strcat 37: Does not concatenate on empty s2");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strcat 42: Does not return s1 on empty s2");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strcat:\tConsistent");
    }
    else
    {
        puts("libc/strcat:\tInconsistent!");
    }
    return err;
}
