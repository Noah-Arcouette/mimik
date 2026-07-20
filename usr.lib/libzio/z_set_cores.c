#include "_zio.h"
#include <errno.h>

int
z_set_cores (zFILE *fp, int cores)
{
	if (!fp || cores < 1)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->options.cores)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	if (fp->options.cores(fp, cores) < 0)
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
