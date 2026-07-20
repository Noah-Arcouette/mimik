#include "_zio.h"
#include <errno.h>

const char *
z_get_original_name (zFILE *fp)
{
	if (!fp)
	{
		errno = EINVAL;
		return NULL;
	}

	zlockfile(fp);

	if (!fp->options.original_name)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return NULL;
	}

	const char *resp = fp->options.original_name(fp, NULL);
	if (!resp)
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return NULL;
	}
	zunlockfile(fp);
	return resp;
}
