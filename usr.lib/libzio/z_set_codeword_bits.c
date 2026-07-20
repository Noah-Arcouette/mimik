#include "_zio.h"
#include <errno.h>

int
z_set_codeword_bits (zFILE *fp, int bits)
{
	if (!fp || bits < 1)
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

	if (fp->options.codeword_bits(fp, bits) < 0)
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
