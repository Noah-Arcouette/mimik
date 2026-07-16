#include "_zio.h"
#include <strings.h>
#include <errno.h>

int
z_format_from_name (const char *name)
{
	if (!name)
	{
		errno = EINVAL;
		return -1;
	}

	switch (name[0])
	{
	case 'l':
	case 'L':
		if (!strcasecmp(name+1, "zw"))
		{
			return ZIO_FORMAT_LZW;
		}
		errno = EINVAL;
		return -1;
	case 'd':
	case 'D':
		if (!strcasecmp(name+1, "eflate"))
		{
			return ZIO_FORMAT_DEFLATE;
		}
		errno = EINVAL;
		return -1;
	case 'g':
	case 'G':
		if (!strcasecmp(name+1, "z"))
		{
			return ZIO_FORMAT_GZIP;
		}
		if (!strcasecmp(name+1, "zip"))
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
