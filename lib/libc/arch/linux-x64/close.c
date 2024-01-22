#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY

int
close (int fildes)
{
    int ret = (int)__syscall1(SYS_CLOSE, fildes);

    if (ret < 0)
    {
        errno = __errnoConvert(ret);
        return -1;
    }
    return 0;
}
