#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[256] = "";
    char *x = strncat(buff, "String", 7);

    if (strcmp(buff, "String"))
    {
        puts("libc/strncat 13: Does not concatenate on empty s1");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncat 18: Does not return s1 on empty s1");
        err = 1;
    }

    x = strncat(buff, "2", 2);
    if (strcmp(buff, "String2"))
    {
        puts("libc/strncat 25: Does not concatenate");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncat 30: Does not return s1");
        err = 1;
    }

    x = strncat(buff, "", 1);
    if (strcmp(buff, "String2"))
    {
        puts("libc/strncat 37: Does not concatenate on empty s2");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncat 42: Does not return s1 on empty s2");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = strncat(buff, "yy", 1);
    if (strncmp(buff, "xxxy", 4))
    {
        puts("libc/strncat 50: Does not partially concatenate");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncat 55: Does not return s1 on partial concatenation");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strncat:\tConsistent");
    }
    else
    {
        puts("libc/strncat:\tInconsistent!");
    }
    return err;
}
