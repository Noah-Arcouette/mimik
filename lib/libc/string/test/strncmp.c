#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    if (strncmp("Same", "Same", 4) != 0)
    {
        puts("libc/strncmp 10: does not return 0 on same strings");
        err = 1;
    }

    if (strncmp("Same1", "Same0", 5) <= 0)
    {
        puts("libc/strncmp 16: does not return more than zero on greater s1");
        err = 1;
    }

    if (strncmp("Same0", "Same1", 5) >= 0)
    {
        puts("libc/strncmp 22: does not return less than zero on lesser s1");
        err = 1;
    }

    if (strncmp("Same", "SameStill", 4) != 0)
    {
        puts("libc/strncmp 28: reads more then specified bytes on s2");
        err = 1;
    }
    if (strncmp("SameStill", "Same", 4) != 0)
    {
        puts("libc/strncmp 33: reads more then specified bytes on s1");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strncmp:\tConsistent");
    }
    else
    {
        puts("libc/strncmp:\tInconsistent!");
    }
    return err;
}
