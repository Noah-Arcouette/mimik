#include <unistd.h>
#include <errno.h>
#include "syscall.h"

int
unlink (const char *path)
{
#ifdef RESILIENT
    if (!path)
    {
        errno = EFAULT;
        return -1;
    }
#endif

    if (!*path)
    {
        errno = ENOENT;
        return -1;
    }

    return (int)__syscall1(0x57, (long)path);
}
