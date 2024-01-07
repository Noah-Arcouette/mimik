#include "../string.h"
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    char buff[256] = "";
    char *x = strncat(buff, "String", 7);

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

    x = strncat(buff, "2", 2);
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

    x = strncat(buff, "", 1);
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

    strcpy(buff, "xxx");
    x = strncat(buff, "yy", 1);
    if (strncmp(buff, "xxxy", 4))
    {
        TITLE();
        puts("Does not partially concatenate");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return s1 on partial concatenation");
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
