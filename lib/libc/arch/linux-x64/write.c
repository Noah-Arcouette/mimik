#include <unistd.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY
#include <errno.h>

ssize_t 
write (int fildes, const void *buf, size_t size)
{
#ifdef RESILIENT
	if (!buf)
	{
		errno = EFAULT;
		return -1;
	}
#endif

	if (size > SSIZE_MAX)
	{
		errno = ERANGE;
		return -1;
	}

	ssize_t ret = __syscall3(SYS_WRITE, fildes, (long)buf, size);

	if (ret < 0)
	{
		errno = __errnoConvert(ret);
		return -1;
	}
	return ret;
}
