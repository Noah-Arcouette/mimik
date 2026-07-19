#ifndef __ZIO_H__
#define __ZIO_H__
#include <pthread.h>
#include <stdio.h>
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

enum _zFILE_backing
{
	_ZFILE_BACKING_FD // file descriptor
};

struct zFILE
{
	#define _ZFILE_FLAGS_READABLE  1ul
	#define _ZFILE_FLAGS_WRITABLE  2ul
	#define _ZFILE_FLAGS_ERROR     4ul
	#define _ZFILE_FLAGS_EOF       8ul
	#define _ZFILE_FLAGS_SECURE   16ul
	unsigned long flags;

	long      locks;
	pthread_t locker;
	_Atomic int lock; // general access lock, no touching locks or locker if set

	enum _zFILE_backing backing;
	union
	{
		int fd;
	};

	int format;

	char buf[BUFSIZ];
	long size;   // amount of data read into the buffer
	long offset; // current offset within the buffer
};

// LZW
/**
 * Return true if the given data in the fp's buffer is an LZW file
 * @param fp The file in question
 * @returns True if the given file is an LZW file
 * @file lzw/_zio_guess_lzw.c
 */
extern int _zio_guess_lzw (zFILE *fp);

/**
 * Setup a lzw file
 * @param fp The file to setup
 * @returns True upon error
 * @file gzip/_zio_setup_lzw.c
 */
extern int _zio_setup_lzw (zFILE *fp);

// Deflate
/**
 * Setup a deflate file
 * @param fp The file to setup
 * @returns True upon error
 * @file gzip/_zio_setup_deflate.c
 */
extern int _zio_setup_deflate (zFILE *fp);

// GZIP
/**
 * Return true if the given data in the fp's buffer is an GZip file
 * @param fp The file in question
 * @returns True if the given file is an GZip file
 * @file gzip/_zio_guess_gzip.c
 */
extern int _zio_guess_gzip (zFILE *fp);

/**
 * Setup a gzip file
 * @param fp The file to setup
 * @returns True upon error
 * @file gzip/_zio_setup_gzip.c
 */
extern int _zio_setup_gzip (zFILE *fp);

#endif
