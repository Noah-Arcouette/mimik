#include "../string.h"
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    char buff[256] = "";
    char *x = strcat(buff, "String");

    if (strcmp(buff, "String"))
    {
        TITLE();
        puts("Does not concatenate on empty s1");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return s1 on empty s1");
        err = 1;
    }

    x = strcat(buff, "2");
    if (strcmp(buff, "String2"))
    {
        TITLE();
        puts("Does not concatenate");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return s1");
        err = 1;
    }

    x = strcat(buff, "");
    if (strcmp(buff, "String2"))
    {
        TITLE();
        puts("Does not concatenate on empty s2");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return s1 on empty s2");
        err = 1;
    }

    if (!err)
    {
        TITLE();
        puts("\tConsistent");
    }
    else
    {
        TITLE();
        puts("\tInconsistent!");
    }
    return err;
}
