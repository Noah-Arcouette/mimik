#include "../string.h"
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    char buff[256];
    void *x = memccpy(buff, "TEST!", 1, 6);
    if (strcmp(buff, "TEST!"))
    {
        TITLE();
        puts("Does not copy to empty dst");
        err = 1;
    }
    if (x != NULL)
    {
        TITLE();
        puts("Does not return NULL with empty dst");
        err = 1;
    }

    x = memccpy(buff, "TEST2!", 1, 7);
    if (strcmp(buff, "TEST2!"))
    {
        TITLE();
        puts("Does not copy to dst");
        err = 1;
    }
    if (x != NULL)
    {
        TITLE();
        puts("Does not return NULL");
        err = 1;
    }

    x = memccpy(buff, "", 1, 1);
    if (strcmp(buff, ""))
    {
        TITLE();
        puts("Does not clear src on empty dst");
        err = 1;
    }
    if (x != NULL)
    {
        TITLE();
        puts("Does not return NULL on empty src");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = memccpy(buff, "yy", 'x', 1);
    if (strcmp(buff, "yxx"))
    {
        TITLE();
        puts("Fixed sized src does not copy properly");
        err = 1;
    }
    if (x != NULL) 
    {
        TITLE();
        puts("Does not return NULL on fixed sized src");
        err = 1;
    }

    x = memccpy(buff, "h", 'h', 2);
    if (strcmp(buff, "hxx"))
    {
        TITLE();
        puts("Does not stop at c");
        err = 1;
    }
    if (x != buff+1)
    {
        TITLE();
        puts("Does not return character after c");
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
