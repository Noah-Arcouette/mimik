#include "_zio.h"

int
z_format_is_compressed (int format)
{
	switch (format)
	{
	case ZIO_FORMAT_DEFAULT_COMPRESS:
		return z_format_is_compressed(_ZIO_DEFAULT_COMPRESS);
	case ZIO_FORMAT_LZW:
	case ZIO_FORMAT_DEFLATE:
	case ZIO_FORMAT_GZIP:
		return 1;
	default:
		return 0;
	}
}
