#include "_zio.h"
#include <stddef.h>
#include <errno.h>

const char *
z_suffix_from_format (int format)
{
	switch (format)
	{
	case ZIO_FORMAT_DEFAULT_COMPRESS:
		return z_suffix_from_format(_ZIO_DEFAULT_COMPRESS);
	case ZIO_FORMAT_LZW:
		return "Z";
	case ZIO_FORMAT_DEFLATE:
		return "deflate";
	case ZIO_FORMAT_GZIP:
		return "gz";
	default:
		errno = EINVAL;
		return NULL;
	}
}
