#include "_zio.h"
#include <errno.h>

int
z_set_original_name (zFILE *fp, const char *name)
{
	if (!fp || !name)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->options.original_name)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	if (!fp->options.original_name(fp, name))
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
