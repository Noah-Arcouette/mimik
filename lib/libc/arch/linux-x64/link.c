#include <unistd.h>
#include <errno.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
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
        errno = __errnoConvert(ret);
        return -1;
    }
    return 0;
}
