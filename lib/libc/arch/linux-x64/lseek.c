#include <unistd.h>
#include <errno.h>
#include "syscall.h"

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

    return (off_t)__syscall3(8, (long)fildes, (long)offset, (long)whence);
}
