#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include "syscall.h"
#undef LINUX_X64_ONLY

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

    int ret = (int)__syscall2(SYS_LINK, (long)src, (long)dst);

    if (ret < 0)
    {
        switch (ret)
        {
            case SYS_EACCES:
                errno = EACCES;
                break;
            case SYS_EDQUOT:
                errno = EDQUOT;
                break;
            case SYS_EEXIST:
                errno = EEXIST;
                break;
            case SYS_EFAULT:
                errno = EFAULT;
                break;
            case SYS_EIO:
                errno = EIO;
                break;
            case SYS_EMLINK:
                errno = EMLINK;
                break;
            case SYS_ENAMETOOLONG:
                errno = ENAMETOOLONG;
                break;
            case SYS_ENOENT:
                errno = ENOENT;
                break;
            case SYS_ENOMEM:
                errno = ENOMEM;
                break;
            case SYS_ENOSPC:
                errno = ENOSPC;
                break;
            case SYS_ENOTDIR:
                errno = ENOTDIR;
                break;
            case SYS_EPERM:
                errno = EPERM;
                break;
            case SYS_EROFS:
                errno = EROFS;
                break;
            case SYS_EXDEV:
                errno = EXDEV;
                break;
            default:
                errno = EUNKNOWN;
                break;
        }

        return -1;
    }
    return 0;
}
