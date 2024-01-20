#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY

off_t
lseek (int fildes, off_t offset, int whence)
{
    int callWhence;
    switch (whence)
    {
    case SEEK_SET:
        if (offset < 0)
        {
            errno = EINVAL;
            return -1;
        }
        callWhence = 0;

        break;
    case SEEK_CUR:
        callWhence = 1;
        break;
    case SEEK_END:
        callWhence = 2;
        break;
    default:
        errno = EINVAL;
        return -1;

        break;
    }

    off_t ret = (off_t)__syscall3(SYS_LSEEK, (long)fildes, (long)offset, (long)callWhence);

    if (ret < 0)
    {
        switch (ret)
        {
            case SYS_EBADF:
                errno = EBADF;
                break;
            case SYS_EINVAL:
                errno = EINVAL;
                break;
            case SYS_ENXIO:
                errno = ENXIO;
                break;
            case SYS_EOVERFLOW:
                errno = EOVERFLOW;
                break;
            case SYS_ESPIPE:
                errno = ESPIPE;
                break;
            default:
                errno = EUNKNOWN;
                break;
        }

        return (off_t)-1;
    }
    return 0;
}
