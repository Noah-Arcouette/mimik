#include "_zio.h"
#include <errno.h>

int
zseeko (zFILE *fp, off_t offset, int whence)
{
	if (!fp ||
		(
			whence != SEEK_SET &&
			whence != SEEK_CUR &&
			whence != SEEK_END
		))
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->formatImpl.seek)
	{
		errno = ENOTSUP;
		zunlockfile(fp);
		return -1;
	}

	int resp = fp->formatImpl.seek(fp, offset, whence);
	zunlockfile(fp);
	return resp;
}
