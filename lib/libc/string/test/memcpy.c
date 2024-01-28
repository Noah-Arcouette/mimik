#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[256];
    char *x = memcpy(buff, "TEST!", 6);
    if (strcmp(buff, "TEST!"))
    {
        puts("libc/memcpy 12: Does not copy to empty dst");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/memcpy 17: Does not return dst on empty dst");
        err = 1;
    }

    x = memcpy(buff, "TEST2!", 7);
    if (strcmp(buff, "TEST2!"))
    {
        puts("libc/memcpy 24: Does not copy to dst");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/memcpy 29: Does not return dst");
        err = 1;
    }

    x = memcpy(buff, "", 1);
    if (strcmp(buff, ""))
    {
        puts("libc/memcpy 36: Does not clear src on empty dst");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/memcpy 41: Does not return dst on empty src");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = memcpy(buff, "yy", 1);
    if (strcmp(buff, "yxx"))
    {
        puts("libc/memcpy 49: Fixed sized src does not copy properly");
        err = 1;
    }
    if (x != buff) 
    {
        puts("libc/memcpy 54: Does not return dst on fixed sized src");
        err = 1;
    }

    if (!err)
    {
        puts("libc/memcpy:\tConsistent");
    }
    else
    {
        puts("libc/memcpy:\tInconsistent!");
    }
    return err;
}
