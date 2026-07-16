#include "_zio.h"

int
z_format_is_encrypted (int format)
{
	switch (format)
	{
	case ZIO_FORMAT_DEFAULT_COMPRESS:
		return z_format_is_encrypted(_ZIO_DEFAULT_COMPRESS);
	case ZIO_FORMAT_LZW:
	case ZIO_FORMAT_DEFLATE:
	case ZIO_FORMAT_GZIP:
	default:
		return 0;
	}
}
