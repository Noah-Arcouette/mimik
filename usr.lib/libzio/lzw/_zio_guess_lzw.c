#include "../_zio.h"
#include <endian.h>

int
_zio_guess_lzw (zFILE *fp)
{
	// seek to start
	if (!fp->backingImpl.seek) return 0;
	if (fp->backingImpl.seek(fp, 0, SEEK_SET) < 0) return 0;

	// read header
	if (!fp->backingImpl.read) return 0;
	struct lzw header;
	if (fp->backingImpl.read(fp, &header, sizeof(header)) != sizeof(header))
	{
		return 0;
	}

	// is it good enough?
	if (le16toh(header.magic) != LZW_MAGIC)
	{
		return 0;
	}

	if (fp->secure)
	{
		if (header.flags & LZW_FLAG_RESERVED) return 0;
	}

	return 1;
}
