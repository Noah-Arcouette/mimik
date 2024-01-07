#include "../string.h"
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    
    if (strlen("TEST") != 4)
    {
        TITLE();
        puts("Does not compute the length of a string");
        err = 1;
    }
    if (strlen(""))
    {
        TITLE();
        puts("Does not compute the length of an empty string");
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
