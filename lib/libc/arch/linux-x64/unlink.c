#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY

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

    int ret = (int)__syscall1(SYS_UNLINK, (long)path);

    if (ret < 0)
    {
        switch (ret)
        {
            case SYS_EACCES:
                errno = EACCES;
                break;
            case SYS_EBUSY:
                errno = EBUSY;
                break;
            case SYS_EFAULT:
                errno = EFAULT;
                break;
            case SYS_EIO:
                errno = EIO;
                break;
            case SYS_EISDIR:
                errno = EISDIR;
                break;
            case SYS_ELOOP:
                errno = ELOOP;
                break;
            case SYS_ENAMETOOLONG:
                errno = ENAMETOOLONG;
                break;
            case SYS_ENOENT:
                errno = ENOENT;
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
            default:
                errno = EUNKNOWN;
                break;
        }

        return -1;
    }
    return 0;
}
