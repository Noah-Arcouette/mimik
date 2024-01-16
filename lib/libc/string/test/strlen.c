#include <string.h>
#include <stdio.h>

int
main (void)
{
    int err = 0;
    
    if (strlen("TEST") != 4)
    {
        puts("libc/strlen 11: Does not compute the length of a string");
        err = 1;
    }
    if (strlen(""))
    {
        puts("libc/strlen 16: Does not compute the length of an empty string");
        err = 1;
    }

    if (!err)
    {
        puts("libc/strlen:\tConsistent");
    }
    else
    {
        puts("libc/strlen:\tInconsistent!");
    }
    return err;
}
