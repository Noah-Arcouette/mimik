#include "_zio.h"
#include <errno.h>

int
z_get_codeword_bits (zFILE *fp)
{
	if (!fp)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->options.codeword_bits)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	int resp = fp->options.codeword_bits(fp, -1);
	if (resp < 0)
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return resp;
}
