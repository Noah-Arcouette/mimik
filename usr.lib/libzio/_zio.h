#ifndef __ZIO_H__
#define __ZIO_H__
#include <zio.h>

// Provide actual definitions and internal definitions

// Compression default
#if defined(DEFAULT_LZW)
#	define _ZIO_DEFAULT_COMPRESS ZIO_FORMAT_LZW
#elif defined(DEFAULT_DEFLATE)
#	define _ZIO_DEFAULT_COMPRESS ZIO_FORMAT_DEFLATE
#elif defined(DEFAULT_GZIP)
#	define _ZIO_DEFAULT_COMPRESS ZIO_FORMAT_GZIP
#else
#	define _ZIO_DEFAULT_COMPRESS ZIO_FORMAT_GZIP // why not
#endif

#endif
