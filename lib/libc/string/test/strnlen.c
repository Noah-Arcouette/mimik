#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    
    if (strnlen("TEST", 5) != 4)
    {
        puts("libc/strnlen 11: Does not compute the length of a string");
        err = 1;
    }
    if (strnlen("", 2))
    {
        puts("libc/strnlen 16: Does not compute the length of an empty string");
        err = 1;
    }

    if (strnlen("TEST", 2) != 2)
    {
        puts("libc/strnlen 22: Does not stop at n");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strnlen:\tConsistent");
    }
    else
    {
        puts("libc/strnlen:\tInconsistent!");
    }
    return err;
}
