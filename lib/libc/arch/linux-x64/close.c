#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY

int
close (int fildes)
{
    int ret = (int)__syscall1(SYS_CLOSE, (long)fildes);

    if (ret < 0)
    {
        switch (ret)
        {
            case SYS_EBADF:
                errno = EBADF;
                break;
            case SYS_EINTR:
                errno = EINTR;
                break;
            case SYS_EIO:
                errno = EIO;
                break;
            case SYS_ENOSPC:
                errno = ENOSPC;
                break;
            case SYS_EDQUOT:
                errno = EDQUOT;
                break;
            default:
                errno = EUNKNOWN;
                break;
        }
        return -1;
    }
    return 0;
}
