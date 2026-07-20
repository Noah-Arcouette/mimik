#include "_zio.h"
#include <errno.h>

int
z_set_compression_level (zFILE *fp, int level)
{
	if (!fp || level < 0)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->options.compression_level)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	if (fp->options.compression_level(fp, level) < 0)
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
