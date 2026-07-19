#include "_zio.h"
#include <errno.h>

int
zseeko (zFILE *fp, off_t offset, int whence)
{
	if (!fp ||
		(whence != SEEK_CUR &&
		whence != SEEK_SET &&
		whence != SEEK_END))
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	// can it seek?
	if (!fp->seek)
	{
		fp->flags |= _ZFILE_FLAGS_ERROR;
		errno = ENOTSUP;
		zunlockfile(fp);
		return -1;
	}

	// flush
	zflush(fp);

	// clear EOF
	fp->flags &= ~_ZFILE_FLAGS_EOF;

	// try to seek
	int resp = fp->seek(fp, offset, whence);
	zunlockfile(fp);

	if (resp >= 0) return 0;
	return -1;
}
