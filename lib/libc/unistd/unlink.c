#include "unistd.h"
#include "../arch/system.h"
#include <errno.h>

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

    return __system_unlink(path);
}
