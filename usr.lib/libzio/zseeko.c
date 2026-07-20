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
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	// flush
	if (fp->formatImpl.flush)
	{
		if (fp->formatImpl.flush(fp))
		{
			int error = errno;
			zunlockfile(fp);
			errno = error;
			return -1;
		}
	}

	// seek
	int resp = fp->formatImpl.seek(fp, offset, whence);
	int error = errno;
	zunlockfile(fp);
	errno = error;
	return resp;
}
