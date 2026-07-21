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
	_ZFILE_BACKING_FD
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
	 * Close implementation specific data (flush was already done)
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
	 * Read data from the file (flushing was done if needed)
	 * @param fp The file to read from
	 * @param buf The buffer to fill
	 * @param amt The amount of bytes to read
	 * @returns The amount of bytes read
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	size_t (*read)(zFILE *restrict fp, void *restrict buf, size_t amt);

	/**
	 * Write data to the file (flushing was done if needed)
	 * @param fp The file to write to
	 * @param buf The buffer to fill
	 * @param amt The amount of bytes to write
	 * @returns The amount of bytes written
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	size_t (*write)(zFILE *restrict fp, const void *restrict buf, size_t amt);

	/**
	 * Seek into the file (flush was already done)
	 * @param fp The file to seek into
	 * @param off The offset to seek to
	 * @param whence Where to seek from
	 * @returns The current offset, or -1 on error
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	off_t (*seek)(zFILE *fp, off_t off, int whence);

	/**
	 * Change underlying ownership
	 * @param fp The file to modify
	 * @param user The user to set to
	 * @param group The group to set
	 * @returns True upon error
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	int (*chown)(zFILE *fp, uid_t user, gid_t group);

	/**
	 * Change underlying mode
	 * @param fp The file to modify
	 * @param mode The mode to set to
	 * @returns True upon error
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	int (*chmod)(zFILE *fp, mode_t mode);

	/**
	 * Change underlying times
	 * @param fp The file to modify
	 * @param t The times to set to: Access time, Modification time
	 * @returns True upon error
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	int (*utimens)(zFILE *fp, struct timespec t[2]);

	/**
	 * Stat a file
	 * @param fp The file to stat
	 * @param statbuf The stat structure to fill
	 * @returns True upon error
	 * @note may and usually should, need to call the backing impl (for format)
	 */
	int (*stat)(zFILE *restrict fp, struct stat *restrict statbuf);
};

// any of these may be null
struct _zFILE_options
{
	/**
	 * Set/get the amount of cores for encoding/decoding
	 * @param fp The file to set
	 * @param cores The cores value (-1 to not set)
	 * @returns The current cores value (-1 if not supported)
	 */
	int (*cores)(zFILE *fp, int cores);

	/**
	 * Set/get the amount of bits for codewords
	 * @param fp The file to set
	 * @param bits The bits value (-1 to not set)
	 * @returns The current bits value (-1 if not supported)
	 */
	int (*codeword_bits)(zFILE *fp, int bits);

	/**
	 * Set/get the encoding level
	 * @param fp The file to set
	 * @param level The level value (-1 to not set)
	 * @returns The current level value (-1 if not supported)
	 */
	int (*compression_level)(zFILE *fp, int level);

	/**
	 * Set/get the original file name
	 * @param fp The file to set
	 * @param name The name to set it to (NULL if only getting)
	 * @returns The current name (or NULL)
	 */
	const char *(*original_name)(zFILE *fp, const char *name);
};

struct zFILE
{
	// flags
	unsigned int error    : 1;
	unsigned int eof      : 1;
	unsigned int readable : 1;
	unsigned int writable : 1;
	unsigned int secure   : 1;
	unsigned int rw       : 1;
	#define _ZFILE_RW_WRITING 0
	#define _ZFILE_RW_READING 1

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
	#ifdef LZW
		struct
		{
			// if the header may be modified (1) or not (0)
			unsigned int headerOpen : 1;
			struct lzw header;
		} lzw;
	#endif
	};
	struct _zFILE_impl formatImpl;
	struct _zFILE_options options;
};

// Backing Impls
#define _ZFILE_NO_IMPL (struct _zFILE_impl){ \
	NULL, /* open */ \
	NULL, /* close */ \
	NULL, /* flush */ \
	NULL, /* sync */ \
	NULL, /* read */ \
	NULL, /* write */ \
	NULL, /* seek */ \
	NULL, /* chown */ \
	NULL, /* chmod */ \
	NULL, /* utimens */ \
	NULL /* stat */ }

// FD
extern int _zio_open_fd (zFILE *fp);
extern int _zio_close_fd (zFILE *fp);
extern int _zio_flush_fd (zFILE *fp);
extern int _zio_sync_fd (zFILE *fp);
extern size_t _zio_read_fd (zFILE *restrict fp, void *restrict buf, size_t amt);
extern size_t _zio_write_fd (zFILE *restrict fp, const void *restrict buf,
	size_t amt);
extern off_t _zio_seek_fd (zFILE *fp, off_t off, int whence);
extern int _zio_chown_fd (zFILE *fp, uid_t user, gid_t group);
extern int _zio_chmod_fd (zFILE *fp, mode_t mode);
extern int _zio_utimens_fd (zFILE *fp, struct timespec t[2]);
extern int _zio_stat_fd (zFILE *restrict fp, struct stat *restrict statbuf);

#define _ZFILE_BACKING_FD_IMPL (struct _zFILE_impl){ \
	_zio_open_fd, /* open */ \
	_zio_close_fd, /* close */ \
	_zio_flush_fd, /* flush */ \
	_zio_sync_fd, /* sync */ \
	_zio_read_fd, /* read */ \
	_zio_write_fd, /* write */ \
	_zio_seek_fd, /* seek */ \
	_zio_chown_fd, /* chown */ \
	_zio_chmod_fd, /* chmod */ \
	_zio_utimens_fd, /* utimens */ \
	_zio_stat_fd /* stat */ }

// Format Impls
// None
extern size_t _zio_read_none (zFILE *restrict fp, void *restrict buf,
	size_t amt);
extern size_t _zio_write_none (zFILE *restrict fp, const void *restrict buf,
	size_t amt);
extern off_t _zio_seek_none (zFILE *fp, off_t off, int whence);
extern int _zio_chown_none (zFILE *fp, uid_t user, gid_t group);
extern int _zio_chmod_none (zFILE *fp, mode_t mode);
extern int _zio_utimens_none (zFILE *fp, struct timespec t[2]);
extern int _zio_stat_none (zFILE *restrict fp, struct stat *restrict statbuf);

#define _ZFILE_FORMAT_NONE_IMPL (struct _zFILE_impl){ \
	NULL, /* open */ \
	NULL, /* close */ \
	NULL, /* flush */ \
	NULL, /* sync */ \
	_zio_read_fd, /* read */ \
	_zio_write_fd, /* write */ \
	_zio_seek_fd, /* seek */ \
	_zio_chown_fd, /* chown */ \
	_zio_chmod_fd, /* chmod */ \
	_zio_utimens_fd, /* utimens */ \
	_zio_stat_fd /* stat */ }
#define _ZFILE_FORMAT_NONE_OPTIONS (struct _zFILE_options){ \
	NULL, /* cores */ \
	NULL, /* code bits*/ \
	NULL, /* level*/ \
	NULL /* original name */ }

// LZW
/**
 * Guess if a file is LZW (must be able to short seek)
 * @param fp The file to guess from
 * @returns True if the file is an LZW
 * @file lzw/_zio_guess_lzw.c
 */
extern int _zio_guess_lzw (zFILE *fp);

extern int _zio_open_lzw (zFILE *fp);

extern int _zio_codeword_bits_lzw (zFILE *fp, int bits);

#ifdef LZW
#	define _ZFILE_FORMAT_LZW_IMPL (struct _zFILE_impl){ \
	_zio_open_lzw, /* open */ \
	NULL, /* close */ \
	NULL, /* flush */ \
	NULL, /* sync */ \
	NULL, /* read */ \
	NULL, /* write */ \
	NULL, /* seek */ \
	NULL, /* chown */ \
	NULL, /* chmod */ \
	NULL, /* utimens */ \
	NULL /* stat */ }
#	define _ZFILE_FORMAT_LZW_OPTIONS (struct _zFILE_options){ \
	NULL, /* cores */ \
	_zio_codeword_bits_lzw, /* code bits*/ \
	NULL, /* level*/ \
	NULL /* original name */ }
#endif

// Deflate
#ifdef DEFLATE
#	define _ZFILE_FORMAT_DEFLATE_IMPL _ZFILE_NO_IMPL
#	define _ZFILE_FORMAT_DEFLATE_OPTIONS _ZFILE_FORMAT_NONE_OPTIONS
#endif

// GZip
/**
 * Guess if a file is GZIP (must be able to short seek)
 * @param fp The file to guess from
 * @returns True if the file is an GZIP
 * @file gzip/_zio_guess_gzip.c
 */
extern int _zio_guess_gzip (zFILE *fp);

#ifdef GZIP
#	define _ZFILE_FORMAT_GZIP_IMPL _ZFILE_NO_IMPL
#	define _ZFILE_FORMAT_GZIP_OPTIONS _ZFILE_FORMAT_NONE_OPTIONS
#endif

#endif
