#include "_zio.h"
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

zFILE *
zdopen (int fildes, const char *restrict mode, int format)
{
	struct zFILE f;

	// setup flags
	f.flags = 0;
	const char *s = mode;
	while (*s)
	{
		switch (*s)
		{
		case 'b':
		case '\0':
		case 'x':
			break;
		case 'e':
			// attempt to set
			if (fcntl(fildes, F_SETFD, FD_CLOEXEC) < 0) return NULL;
			break;
		case 'r':
			f.flags |= _ZFILE_FLAGS_READABLE;
			break;
		case 'w':
		case 'a':
			f.flags |= _ZFILE_FLAGS_WRITABLE;
			break;
		case '+':
			f.flags |= _ZFILE_FLAGS_WRITABLE | _ZFILE_FLAGS_READABLE;
			break;
		case 's':
			f.flags |= _ZFILE_FLAGS_SECURE;
			break;
		default:
			errno = EINVAL;
			return NULL;
		}
		s++;
	}

	f.locks = 0;
	f.lock  = 0; // leave it unlocked for now

	// setup backing
	f.backing = _ZFILE_BACKING_FD;
	f.fd      = fildes;

	// clear up data
	f.size   = 0;
	f.offset = 0;

	// setup format
	if (format == ZIO_FORMAT_DEFAULT_COMPRESS) format = _ZIO_DEFAULT_COMPRESS;
	switch (format)
	{
	case ZIO_FORMAT_NONE:
		f.format = format;
		break; // all good
	case ZIO_FORMAT_LZW:
	#ifndef LZW
		errno = ENOSYS;
		return NULL;
	#endif
		f.format = format;
		break; // all good
	case ZIO_FORMAT_DEFLATE:
	#ifndef DEFLATE
		errno = ENOSYS;
		return NULL;
	#endif
		f.format = format;
		break; // all good
	case ZIO_FORMAT_GZIP:
	#ifndef GZIP
		errno = ENOSYS;
		return NULL;
	#endif
		f.format = format;
		break; // all good
	case -1:
		// not readable
		if (!(f.flags & _ZFILE_FLAGS_READABLE))
		{
			errno = ENOTSUP;
			return NULL;
		}

		// fill the internal buffer
		ssize_t amt = read(fildes, f.buf, sizeof(f.buf));
		if (amt < 0)
		{
			return NULL;
		}
		f.size   = amt;
		f.offset = 0;

		// guess the format
	#ifdef LZW
		if (_zio_guess_lzw(&f))
		{
			f.format = ZIO_FORMAT_LZW;
		}
		else
	#endif
	#ifdef GZIP
		if (_zio_guess_gzip(&f))
		{
			f.format = ZIO_FORMAT_GZIP;
		}
		else
	#endif
		{
			errno = ENOSYS;
			return NULL;
		}
		break;
	default:
		errno = EINVAL;
		return NULL;
	}

	// check if it can be opened as a file
	if (!z_format_is_filed(f.format))
	{
		errno = EISDIR;
		return NULL;
	}

	// all good

	// duplicate
	zFILE *fp = malloc(sizeof(zFILE));
	if (!fp) return NULL;
	memcpy(fp, &f, sizeof(f));

	// setup format
	switch (f.format)
	{
	case ZIO_FORMAT_NONE:
		if (_zio_setup_none(fp))
		{
			free(fp);
			return NULL;
		}
		break;
	#ifdef LZW
	case ZIO_FORMAT_LZW:
		if (_zio_setup_lzw(fp))
		{
			free(fp);
			return NULL;
		}
		break;
	#endif
	#ifdef DEFLATE
	case ZIO_FORMAT_DEFLATE:
		if (_zio_setup_deflate(fp))
		{
			free(fp);
			return NULL;
		}
		break;
	#endif
	#ifdef GZIP
	case ZIO_FORMAT_GZIP:
		if (_zio_setup_gzip(fp))
		{
			free(fp);
			return NULL;
		}
		break;
	#endif
	}

	// return
	return fp;
}
