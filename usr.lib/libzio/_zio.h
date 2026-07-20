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

	/// @note BIG NOTE: the none options send the request to the backing for
	/// VFS based things this is almost always needed to be called, please keep
	/// that in-mind for implementation

	/**
	 * Read from backing into *buf* (dencoding)
	 */
	size_t (*read)(zFILE *restrict fp, void *restrict buf, size_t size);

	/**
	 * Write from *buf* into backing (encoding)
	 */
	size_t (*write)(zFILE *restrict fp, const void *restrict buf, size_t size);

	/**
	 * Seek, if possible
	 */
	off_t (*seek)(zFILE *fp, off_t offset, int whence);

	/**
	 * VFS options, usually just pass down to backing
	 */
	int (*stat)   (zFILE *restrict fp, struct stat *restrict statbuf);
	int (*chown)  (zFILE *fp, uid_t user, gid_t group);
	int (*chmod)  (zFILE *fp, mode_t mode);
	int (*utimens)(zFILE *fp, struct timespec t[2]);

	// backing data buffer (main i/o to the backing)
	char  *buf;
	size_t bufcp; // capacity of the buffer
	size_t bufsz; // amount of data in the buffer
	size_t bufof; // offset of the data in the buffer (for reading)
};

// None
/**
 * Setup only for backing file
 * @param fp The file in question
 * @returns True upon error
 * @file none/_zio_setup_none.c
 */
extern int _zio_setup_none (zFILE *fp);

/**
 * Read from backing into buffer
 * @note useful for other implementation to get backing data
 * @param fp The file in question
 * @param buf The buffer to fill
 * @param size The amount to read
 * @returns The amount read, will set error flag and errno on error
 * @file none/_zio_read_none.c
 */
extern size_t _zio_read_none (zFILE *restrict fp, void *restrict buf,
	size_t size);

/**
 * Write to backing from buffer
 * @note useful for other implementation to put backing data
 * @param fp The file in question
 * @param buf The buffer to read from
 * @param size The amount to write
 * @returns The amount written, will set error flag and errno on error
 * @file none/_zio_write_none.c
 */
extern size_t _zio_write_none (zFILE *restrict fp, const void *restrict buf,
	size_t size);

/**
 * Seek into the backing device
 * @note useful for other implementation to seek the backing device
 * @param fp The file in question
 * @param offset The offset to seek to
 * @param whence Starting point of the seek
 * @returns The current offset (the tell), or -1 on error
 * @file none/_zio_seek_none.c
 */
extern off_t _zio_seek_none (zFILE *fp, off_t offset, int whence);

/**
 * Stat the backing device
 * @note useful for other implementation to stat the backing device
 * @param fp The file in question
 * @param statbuf The stat buffer to fill
 * @returns Non-zero on failure
 * @file none/_zio_stat_none.c
 */
extern int _zio_stat_none (zFILE *restrict fp, struct stat *restrict statbuf);

/**
 * Change ownership the backing device
 * @note useful for other implementation to update the backing device
 * @param fp The file in question
 * @param user The user to set to
 * @param group The group to set to
 * @returns Non-zero on failure
 * @file none/_zio_chown_none.c
 */
extern int _zio_chown_none (zFILE *fp, uid_t user, gid_t group);

/**
 * Change mode the backing device
 * @note useful for other implementation to update the backing device
 * @param fp The file in question
 * @param mode The mode to set to
 * @returns Non-zero on failure
 * @file none/_zio_chmod_none.c
 */
extern int _zio_chmod_none (zFILE *fp, mode_t mode);

/**
 * Change times the backing device
 * @note useful for other implementation to update the backing device
 * @param fp The file in question
 * @param t Access time, modification time
 * @returns Non-zero on failure
 * @file none/_zio_utimens_none.c
 */
extern int _zio_utimens_none (zFILE *fp, struct timespec t[2]);

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
