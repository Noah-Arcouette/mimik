#include <unistd.h>
#include <errno.h>
#include "syscall.h"

int
link (const char *src, const char *dst)
{
#ifdef RESILIENT
    if (!src || !dst)
    {
        errno = EFAULT;
        return -1;
    }
#endif

    if (!*src || !*dst)
    {
        errno = ENOENT;
        return -1;
    }

    return (int)__syscall2(0x56, (long)src, (long)dst);
}
