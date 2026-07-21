#include "../_zio.h"
#include <errno.h>

int
_zio_codeword_bits_lzw (zFILE *fp, int bits)
{
	if ((bits >= 0 && bits < 9) || bits > 31)
	{
		errno = EINVAL;
		return -1;
	}

	// setter
	if (bits >= 0)
	{
		if (!fp->lzw.headerOpen)
		{
			errno = ENOTSUP;
			return -1;
		}
		// set it
		fp->lzw.header.flags =
			(fp->lzw.header.flags & ~LZW_FLAG_CODE_BITS_MASK) | bits;
	}

	// getter
	return fp->lzw.header.flags & LZW_FLAG_CODE_BITS_MASK;
}
