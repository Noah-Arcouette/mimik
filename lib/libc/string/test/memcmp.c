#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    if (memcmp("Same", "Same", 4) != 0)
    {
        puts("libc/memcmp 10: does not return 0 on same data");
        err = 1;
    }

    if (memcmp("Same1", "Same0", 5) <= 0)
    {
        puts("libc/memcmp 16: does not return more than zero on greater s1");
        err = 1;
    }

    if (memcmp("Same0", "Same1", 5) >= 0)
    {
        puts("libc/memcmp 22: does not return less than zero on lesser s1");
        err = 1;
    }

    if (memcmp("Same", "SameStill", 4) != 0)
    {
        puts("libc/memcmp 28: reads more then specified bytes on s2");
        err = 1;
    }
    if (memcmp("SameStill", "Same", 4) != 0)
    {
        puts("libc/memcmp 33: reads more then specified bytes on s1");
        err = 1;
    }

    if (!err)
    {
        puts("libc/memcmp:\tConsistent");
    }
    else
    {
        puts("libc/memcmp:\tInconsistent!");
    }
    return err;
}
