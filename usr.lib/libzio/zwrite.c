#include "_zio.h"
#include <errno.h>

size_t
zwrite (const void *restrict buf, size_t size, size_t n, zFILE *restrict fp)
{
	if (!fp)
	{
		errno = EINVAL;
		return 0;
	}

	if (size == 0 || n == 0) return 0;

	zlockfile(fp);
	if (!buf)
	{
		fp->flags |= _ZFILE_FLAGS_ERROR;
		errno = EINVAL;
		zunlockfile(fp);
		return 0;
	}

	const char *dat = buf;
	size_t amt;

	for (amt = 0; amt<n; amt++)
	{
		for (size_t i = 0; i<size; i++)
		{
			if (zputc_unlocked(*dat, fp) == EOF)
			{
				zunlockfile(fp);
				return amt;
			}
			dat++; // gross but it works
		}
	}

	zunlockfile(fp);
	return amt;
}
