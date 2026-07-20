#include "../_zio.h"
#include <endian.h>

int
_zio_guess_gzip (zFILE *fp)
{
	// seek to start
	if (!fp->backingImpl.seek) return 0;
	if (fp->backingImpl.seek(fp, 0, SEEK_SET) < 0) return 0;

	// read header
	if (!fp->backingImpl.read) return 0;
	struct gzip header;
	if (fp->backingImpl.read(fp, &header, sizeof(header)) != sizeof(header))
	{
		return 0;
	}

	// is it good enough?
	if (le16toh(header.magic) != GZIP_MAGIC)
	{
		return 0;
	}
	if (header.method != GZIP_METHOD_DEFLATE)
	{
		return 0;
	}

	if (fp->secure)
	{
		if (header.flags & GZIP_FLAG_RESERVED) return 0;
	}

	return 1;
}
