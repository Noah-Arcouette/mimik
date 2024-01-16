#include <string.h>
#include <stdio.h>

void *memccpy (void *, const void *, int, size_t);

int
main (void)
{
    int err = 0;
    char buff[256];
    void *x = memccpy(buff, "TEST!", 1, 6);
    if (strcmp(buff, "TEST!"))
    {
        puts("libc/memccpy 12: Does not copy to empty dst");
        err = 1;
    }
    if (x != NULL)
    {
        puts("libc/memccpy 17: Does not return NULL with empty dst");
        err = 1;
    }

    x = memccpy(buff, "TEST2!", 1, 7);
    if (strcmp(buff, "TEST2!"))
    {
        puts("libc/memccpy 24: Does not copy to dst");
        err = 1;
    }
    if (x != NULL)
    {
        puts("libc/memccpy 29: Does not return NULL");
        err = 1;
    }

    x = memccpy(buff, "", 1, 1);
    if (strcmp(buff, ""))
    {
        puts("libc/memccpy 36: Does not clear src on empty dst");
        err = 1;
    }
    if (x != NULL)
    {
        puts("libc/memccpy 41: Does not return NULL on empty src");
        err = 1;
    }

    strcpy(buff, "xxx");
    x = memccpy(buff, "yy", 'x', 1);
    if (strcmp(buff, "yxx"))
    {
        puts("libc/memccpy 49: Fixed sized src does not copy properly");
        err = 1;
    }
    if (x != NULL) 
    {
        puts("libc/memccpy 54: Does not return NULL on fixed sized src");
        err = 1;
    }

    x = memccpy(buff, "h", 'h', 2);
    if (strcmp(buff, "hxx"))
    {
        puts("libc/memccpy 61: Does not stop at c");
        err = 1;
    }
    if (x != buff+1)
    {
        puts("libc/memccpy 66: Does not return character after c");
        err = 1;
    }

    if (!err)
    {
        puts("libc/memccpy:\tConsistent");
    }
    else
    {
        puts("libc/memccpy:\tInconsistent!");
    }
    return err;
}
