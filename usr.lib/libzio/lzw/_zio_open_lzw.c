#include "../_zio.h"
#include <endian.h>
#include <errno.h>

int
_zio_open_lzw (zFILE *fp)
{
	// no update mode supported
	if (fp->readable && fp->writable)
	{
		errno = EINVAL;
		return -1;
	}

	if (fp->readable)
	{
		// seek to start
		if (fp->backingImpl.seek) fp->backingImpl.seek(fp, 0, SEEK_SET);

		// read it in
		if (!fp->backingImpl.read)
		{
			errno = ENOTSUP;
			return -1;
		}
		if (fp->backingImpl.read(fp, &fp->lzw.header, sizeof(struct lzw)) !=
			sizeof(struct lzw))
		{
			errno = EBADMSG;
			return -1;
		}

		// double check its valid
		fp->lzw.headerOpen = 0;
		if (le16toh(fp->lzw.header.magic) != LZW_MAGIC)
		{
			errno = EBADMSG;
			return -1;
		}
		if ((fp->lzw.header.flags & LZW_FLAG_CODE_BITS_MASK) < 9)
		{
			errno = EBADMSG;
			return -1;
		}
		if (fp->secure)
		{
			if (fp->lzw.header.flags & LZW_FLAG_RESERVED)
			{
				errno = EBADMSG;
				return -1;
			}
		}
		return 0;
	}
	else
	{
		// create it defaultily
		fp->lzw.headerOpen = 1;
		fp->lzw.header.magic = htole16(LZW_MAGIC);
		fp->lzw.header.flags = 16 | LZW_FLAG_BLOCK_MODE;
		return 0;
	}
}
