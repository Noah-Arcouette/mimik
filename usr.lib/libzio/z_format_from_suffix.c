#include "_zio.h"
#include <strings.h>
#include <string.h>
#include <errno.h>

int
z_format_from_suffix (const char *suffix)
{
	if (!suffix)
	{
		errno = EINVAL;
		return -1;
	}

	if (suffix[0] == '.') suffix++; // allow periods

	switch (suffix[0])
	{
	case 'Z':
		if (suffix[1] == 0)
		{
			return ZIO_FORMAT_LZW;
		}
		errno = EINVAL;
		return -1;
	case 'd':
	case 'D':
		if (!strcasecmp(suffix+1, "eflate"))
		{
			return ZIO_FORMAT_DEFLATE;
		}
		errno = EINVAL;
		return -1;
	case 'g':
	case 'G':
		if (!strcasecmp(suffix+1, "z"))
		{
			return ZIO_FORMAT_GZIP;
		}
		if (!strcasecmp(suffix+1, "zip"))
		{
			return ZIO_FORMAT_GZIP;
		}
		errno = EINVAL;
		return -1;
	default:
		errno = EINVAL;
		return -1;
	}
}
