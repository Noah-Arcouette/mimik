#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    char buff[5];

    char *x = memset(buff, 7, 3);
    if (buff[0] != 7 || buff[1] != 7 || buff[2] != 7)
    {
        puts("libc/memset 13: Does not set s to c");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/memset 18: Does not return s");
        err = 1;
    }

    x = memset(buff, 2, 2);
    if (buff[2] != 7)
    {
        puts("libc/memset 25: Sets more than specified");
        err = 1;
    }
    if (x != buff)
    {
        puts("libc/memset 30: Does not return s, on over write");
        err = 1;
    }

    if (!err)
    {
        puts("libc/memset:\tConsistent");
    }
    else
    {
        puts("libc/memset:\tInconsistent!");
    }
    return err;
}
