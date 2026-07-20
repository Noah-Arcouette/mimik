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
	f.error    = 0;
	f.eof      = 0;
	f.readable = 0;
	f.writable = 0;
	f.secure   = 0;
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
			f.readable = 1;
			break;
		case 'w':
		case 'a':
			f.writable = 1;
			break;
		case '+':
			f.readable = 1;
			f.writable = 1;
			break;
		case 's':
			f.secure = 1;
			break;
		default:
			errno = EINVAL;
			return NULL;
		}
		s++;
	}

	// setup locks
	f.lock   = 0;
	f.locker = 0;
	f.locks  = 0;

	// setup backing
	f.backing = _ZFILE_BACKING_FD;
	f.fd.fd = fildes;
	f.backingImpl = _ZFILE_BACKING_FD_IMPL;

	if (f.backingImpl.open(&f)) return NULL;

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
	#else
		f.format = format;
		break; // all good
	#endif
	case ZIO_FORMAT_DEFLATE:
	#ifndef DEFLATE
		errno = ENOSYS;
		return NULL;
	#else
		f.format = format;
		break; // all good
	#endif
	case ZIO_FORMAT_GZIP:
	#ifndef GZIP
		errno = ENOSYS;
		return NULL;
	#else
		f.format = format;
		break; // all good
	#endif
	case -1:
		// not readable
		if (!f.readable)
		{
			errno = ENOTSUP;
			if (f.backingImpl.close) f.backingImpl.close(&f);
			return NULL;
		}

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
			if (f.backingImpl.close) f.backingImpl.close(&f);
			return NULL;
		}
		break;
	default:
		errno = EINVAL;
		if (f.backingImpl.close) f.backingImpl.close(&f);
		return NULL;
	}

	// check if it can be opened as a file
	if (!z_format_is_filed(f.format))
	{
		errno = EISDIR;
		if (f.backingImpl.close) f.backingImpl.close(&f);
		return NULL;
	}

	// all good

	// duplicate
	zFILE *fp = malloc(sizeof(zFILE));
	if (!fp)
	{
		if (f.backingImpl.close) f.backingImpl.close(&f);
		return NULL;
	}
	memcpy(fp, &f, sizeof(f));

	// setup format
	switch (f.format)
	{
	case ZIO_FORMAT_NONE:
		fp->formatImpl = _ZFILE_FORMAT_NONE_IMPL;
		break;
	#ifdef LZW
	case ZIO_FORMAT_LZW:
		fp->formatImpl = _ZFILE_FORMAT_LZW_IMPL;
		break;
	#endif
	#ifdef DEFLATE
	case ZIO_FORMAT_DEFLATE:
		fp->formatImpl = _ZFILE_FORMAT_DEFLATE_IMPL;
		break;
	#endif
	#ifdef GZIP
	case ZIO_FORMAT_GZIP:
		fp->formatImpl = _ZFILE_FORMAT_GZIP_IMPL;
		break;
	#endif
	}

	// open it
	if (fp->formatImpl.open)
	{
		if (fp->formatImpl.open(fp))
		{
			zclose(fp);
			return NULL;
		}
	}

	// return
	return fp;
}
