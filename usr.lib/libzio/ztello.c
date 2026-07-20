#include "_zio.h"
#include <errno.h>

off_t
ztell (zFILE *fp)
{
	if (!fp)
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

	// tell
	off_t resp = fp->formatImpl.seek(fp, 0, SEEK_CUR);
	int error = errno;
	zunlockfile(fp);
	errno = error;
	return resp;
}
