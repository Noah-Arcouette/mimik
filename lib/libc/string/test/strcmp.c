#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    if (strcmp("Same", "Same") != 0)
    {
        puts("libc/strcmp 10: does not return 0 on same strings");
        err = 1;
    }

    if (strcmp("Same1", "Same0") <= 0)
    {
        puts("libc/strcmp 16: does not return more than zero on greater s1");
        err = 1;
    }

    if (strcmp("Same0", "Same1") >= 0)
    {
        puts("libc/strcmp 22: does not return less than zero on lesser s1");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strcmp:\tConsistent");
    }
    else
    {
        puts("libc/strcmp:\tInconsistent!");
    }
    return err;
}
