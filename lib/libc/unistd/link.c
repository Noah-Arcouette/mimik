#include <unistd.h>
#include "../arch/system.h"
#include <errno.h>

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

    return __system_link(src, dst);
}
