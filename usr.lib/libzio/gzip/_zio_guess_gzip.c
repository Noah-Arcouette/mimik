#include "../_zio.h"
#include <endian.h>

int
_zio_guess_gzip (zFILE *fp)
{
	if (fp->size < 2)
	{
		return 0;
	}

	uint16_t dat = fp->buf[0] | (fp->buf[1]<<8);
	if (dat == GZIP_MAGIC)
	{
		return 1;
	}

	return 0;
}
