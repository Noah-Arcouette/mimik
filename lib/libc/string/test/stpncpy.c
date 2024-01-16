#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[256];
    char *x = stpncpy(buff, "TEST!", 6);
    if (strcmp(buff, "TEST!"))
    {
        puts("libc/stpncpy 12: Does not copy to empty dst");
        err = 1;
    }
    if (x != buff+5)
    {
        puts("libc/stpncpy 17: Does not return end of dst on empty dst");
        err = 1;
    }

    x = stpncpy(buff, "TEST2!", 7);
    if (strcmp(buff, "TEST2!"))
    {
        puts("libc/stpncpy 24: Does not copy to dst");
        err = 1;
    }
    if (x != buff+6)
    {
        puts("libc/stpncpy 29: Does not return end of dst");
        err = 1;
    }

    x = stpncpy(buff, "", 1);
    if (strcmp(buff, ""))
    {
        puts("libc/stpncpy 36: Does not clear src on empty dst");
        err = 1;
    }
    if (x != buff+0)
    {
        puts("libc/stpncpy 41: Does not return end of dst on empty src");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = stpncpy(buff, "yy", 1);
    if (strcmp(buff, "yxx"))
    {
        puts("libc/stpncpy 49: Fixed sized src does not copy properly");
        err = 1;
    }
    if (x != buff+1) 
    {
        puts("libc/stpncpy 54: Does not return end of dst on fixed sized src");
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
