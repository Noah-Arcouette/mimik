#include "../string.h"
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    if (strncmp("Same", "Same", 4) != 0)
    {
        TITLE();
        puts("does not return 0 on same strings");
        err = 1;
    }

    if (strncmp("Same1", "Same0", 5) <= 0)
    {
        TITLE();
        puts("does not return more than zero on greater s1");
        err = 1;
    }

    if (strncmp("Same0", "Same1", 5) >= 0)
    {
        TITLE();
        puts("does not return less than zero on lesser s1");
        err = 1;
    }

    if (strncmp("Same", "SameStill", 4) != 0)
    {
        TITLE();
        puts("reads more then specified bytes on s2");
        err = 1;
    }
    if (strncmp("SameStill", "Same", 4) != 0)
    {
        TITLE();
        puts("reads more then specified bytes on s1");
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
