#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include "syscall.h"
#undef LINUX_X64_ONLY

off_t
lseek (int fildes, off_t offset, int whence)
{
    switch (whence)
    {
    case SEEK_SET:
        if (offset < 0)
        {
            errno = EINVAL;
            return -1;
        }

        break;
    case SEEK_CUR:
    case SEEK_END:
        break;
    default:
        errno = EINVAL;
        return -1;

        break;
    }

    return (off_t)__syscall3(SYS_LSEEK, (long)fildes, (long)offset, (long)whence);
}
