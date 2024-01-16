#include "unistd.h"
#include "../arch/system.h"
#include <errno.h>

int
link (const char *old, const char *new)
{
#ifdef RESILIENT
    if (!old || !new)
    {
        errno = EFAULT;
        return -1;
    }
#endif

    return __system_link(old, new);
}
