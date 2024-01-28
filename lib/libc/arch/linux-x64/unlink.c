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
		errno = __errnoConvert(ret);
		return -1;
	}
	return 0;
}
