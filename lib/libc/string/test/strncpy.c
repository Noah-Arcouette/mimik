#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[256];
    char *x = strncpy(buff, "TEST!", 6);
    if (strcmp(buff, "TEST!"))
    {
        puts("libc/strncpy 12: Does not copy to empty dst");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncpy 17: Does not return dst on empty dst");
        err = 1;
    }

    x = strncpy(buff, "TEST2!", 7);
    if (strcmp(buff, "TEST2!"))
    {
        puts("libc/strncpy 24: Does not copy to dst");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncpy 29: Does not return dst");
        err = 1;
    }

    x = strncpy(buff, "", 1);
    if (strcmp(buff, ""))
    {
        puts("libc/strncpy 36: Does not clear src on empty dst");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/strncpy 41: Does not return dst on empty src");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = strncpy(buff, "yy", 1);
    if (strcmp(buff, "yxx"))
    {
        puts("libc/strncpy 49: Fixed sized src does not copy properly");
        err = 1;
    }
    if (x != buff) 
    {
        puts("libc/strncpy 54: Does not return dst on fixed sized src");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strncpy:\tConsistent");
    }
    else
    {
        puts("libc/strncpy:\tInconsistent!");
    }
    return err;
}
