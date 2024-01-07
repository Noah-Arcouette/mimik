#include "../string.h"
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    char buff[5];

    char *x = memset(buff, 7, 3);
    if (buff[0] != 7 || buff[1] != 7 || buff[2] != 7)
    {
        TITLE();
        puts("Does not set s to c");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return s");
        err = 1;
    }

    x = memset(buff, 2, 2);
    if (buff[2] != 7)
    {
        TITLE();
        puts("Sets more than specified");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return s, on over write");
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
