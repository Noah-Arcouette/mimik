#include "_zio.h"

int
z_format_is_filed (int format)
{
	switch (format)
	{
	case ZIO_FORMAT_DEFAULT_COMPRESS:
		return z_format_is_archived(_ZIO_DEFAULT_COMPRESS);
	case ZIO_FORMAT_NONE:
	case ZIO_FORMAT_GZIP:
	case ZIO_FORMAT_LZW:
	case ZIO_FORMAT_DEFLATE:
		return 1;
	default:
		return 0;
	}
}
