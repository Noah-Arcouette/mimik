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
	_zFILE_BACKING_FD
};

// any of the defined functions may also be NULL
struct _zFILE_impl
{
	/**
	 * Setup, allocate, or otherwise initialize the implementation specific data
	 * @param fp The file pointer to initialize
	 * @returns True upon error
	 */
	int (*open)(zFILE *fp);

	/**
	 * Close implementation specific data
	 * @param fp The file pointer to free
	 * @returns True upon error
	 */
	int (*close)(zFILE *fp);

	/**
	 * Flush any buffered data
	 * @param fp The file pointer to flush
	 * @returns True upon error
	 */
	int (*flush)(zFILE *fp);

	/**
	 * Sync the underlying data if needed (as-well as flushing)
	 * @param fp The file pointer to sync
	 * @returns True upon error
	 */
	int (*sync)(zFILE *fp);

	/**
	 * Read data from the file
	 * @param fp The file to read from
	 * @param buf The buffer to fill
	 * @param amt The amount of bytes to read
	 * @returns The amount of bytes read
	 */
	size_t (*read)(zFILE *restrict fp, void *restrict buf, size_t amt);

	/**
	 * Write data to the file
	 * @param fp The file to write to
	 * @param buf The buffer to fill
	 * @param amt The amount of bytes to write
	 * @returns The amount of bytes written
	 */
	size_t (*write)(zFILE *restrict fp, const void *restrict buf, size_t amt);

	/**
	 * Seek into the file
	 * @param fp The file to seek into
	 * @param off The offset to seek to
	 * @param whence Where to seek from
	 * @returns The current offset, or -1 on error
	 */
	off_t (*seek)(zFILE *fp, off_t off, int whence);

	/**
	 * Change underlying ownership
	 * @param fp The file to modify
	 * @param user The user to set to
	 * @param group The group to set
	 * @returns True upon error
	 */
	int (*chown)(zFILE *fp, uid_t user, gid_t group);

	/**
	 * Change underlying mode
	 * @param fp The file to modify
	 * @param mode The mode to set to
	 * @returns True upon error
	 */
	int (*chmod)(zFILE *fp, mode_t mode);

	/**
	 * Change underlying times
	 * @param fp The file to modify
	 * @param t The times to set to: Access time, Modification time
	 * @returns True upon error
	 */
	int (*utimens)(zFILE *fp, struct timespec t[2]);

	/**
	 * Stat a file
	 * @param fp The file to stat
	 * @param statbuf The stat structure to fill
	 * @returns True upon error
	 */
	int (*stat)(zFILE *restrict fp, struct stat *restrict statbuf);
};

struct zFILE
{
	// flags
	unsigned int error    : 1;
	unsigned int eof      : 1;
	unsigned int readable : 1;
	unsigned int writable : 1;
	unsigned int secure   : 1;

	volatile int lock; // general access lock
	pthread_t locker;  // owner of the locks
	long locks;       // the amount of locks open

	// backing data
	enum _zFILE_backing backing;
	union
	{
		struct
		{
			int    fd;    // file descriptor
			char  *buf;   // the buffer
			size_t bufcp; // the buffer capacity
			size_t bufsz; // size of the data in the buffer
			size_t bufof; // offset of the data in the buffer
		} fd;
	};
	struct _zFILE_impl backingImpl;

	// the format data
	int format;
	union
	{
		// void none;
	};
	struct _zFILE_impl formatImpl;
};

#endif
