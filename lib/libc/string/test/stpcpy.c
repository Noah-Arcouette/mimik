#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[256];
    char *x = stpcpy(buff, "TEST!");
    if (strcmp(buff, "TEST!"))
    {
        puts("libc/stpcpy 12: Does not copy to empty dst");
        err = 1;
    }
    if (*x)
    {
        puts("libc/stpcpy 17: Does not return end of dst on empty dst");
        err = 1;
    }

    x = stpcpy(buff, "TEST2!");
    if (strcmp(buff, "TEST2!"))
    {
        puts("libc/stpcpy 24: Does not copy to dst");
        err = 1;
    }
    if (*x)
    {
        puts("libc/stpcpy 29: Does not return end of dst\n");
        err = 1;
    }

    x = stpcpy(buff, "");
    if (strcmp(buff, ""))
    {
        puts("libc/stpcpy 36: Does not clear src on empty dst");
        err = 1;
    }
    if (*x)
    {
        puts("libc/stpcpy 41: Does not return end of dst on empty src");
        err = 1;
    }

    if (!err)
    {
        puts("libc/stpcpy:\tConsistent");
    }
    else
    {
        puts("libc/stpcpy:\tInconsistent!");
    }
    return err;
}
