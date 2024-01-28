#include <string.h>
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    int err = 0;
    char buff[256];
    char *x = strncpy(buff, "TEST!", 6);
    if (strcmp(buff, "TEST!"))
    {
        TITLE();
        puts("Does not copy to empty dst");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return dst on empty dst");
        err = 1;
    }

    x = strncpy(buff, "TEST2!", 7);
    if (strcmp(buff, "TEST2!"))
    {
        TITLE();
        puts("Does not copy to dst");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return dst");
        err = 1;
    }

    x = strncpy(buff, "", 1);
    if (strcmp(buff, ""))
    {
        TITLE();
        puts("Does not clear src on empty dst");
        err = 1;
    }
    if (x != buff)
    {
        TITLE();
        puts("Does not return dst on empty src");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = strncpy(buff, "yy", 1);
    if (strcmp(buff, "yxx"))
    {
        TITLE();
        puts("Fixed sized src does not copy properly");
        err = 1;
    }
    if (x != buff) 
    {
        TITLE();
        puts("Does not return dst on fixed sized src");
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
