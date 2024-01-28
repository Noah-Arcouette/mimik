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

	off_t ret = (off_t)__syscall3(SYS_LSEEK, fildes, offset, callWhence);

	if (ret < 0)
	{
		errno = __errnoConvert(ret);
		return (off_t)-1;
	}
	return 0;
}
