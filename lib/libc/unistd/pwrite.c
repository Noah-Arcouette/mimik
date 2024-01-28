#include <unistd.h>

ssize_t 
pwrite (int fildes, const void *buf, size_t size, off_t offset)
{
    if (lseek(fildes, offset, SEEK_SET) < 0)
    {
        return -1;
    }

    return write(fildes, buf, size);
}
