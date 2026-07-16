#ifndef __INCLUDE_ZIO_H__
#define __INCLUDE_ZIO_H__
#include <sys/types.h>
#include <sys/stat.h>

/// @defgroup Formats
// Defaults
#define ZIO_FORMAT_DEFAULT_COMPRESS 0
// Misc
#define ZIO_FORMAT_LZW 10
// Deflate based
#define ZIO_FORMAT_DEFLATE 20
#define ZIO_FORMAT_GZIP    21

/// @defgroup Helper functions
/**
 * Check if a format is compressed
 * @param format The format in question
 * @returns True if the given format is compressed
 * @file usr.lib/libzio/z_format_is_compressed.c
 */
extern int z_format_is_compressed (int format);

/**
 * Check if a format is archived
 * @param format The format in question
 * @returns True if the given format is archived
 * @file usr.lib/libzio/z_format_is_archived.c
 */
extern int z_format_is_archived (int format);

/**
 * Check if a format is protected
 * @param format The format in question
 * @returns True if the given format is protected
 * @file usr.lib/libzio/z_format_is_protected.c
 */
extern int z_format_is_protected (int format);

/**
 * Check if a format is encrypted
 * @param format The format in question
 * @returns True if the given format is encrypted
 * @file usr.lib/libzio/z_format_is_encrypted.c
 */
extern int z_format_is_encrypted (int format);

/**
 * Get the suffix of a format (not including period)
 * @param format The format in question
 * @returns A static string of the given suffix, or null
 * @file usr.lib/libzio/z_suffix_from_format.c
 */
extern const char *z_suffix_from_format (int format);

/**
 * Get the format based on the given suffix (without a period)
 * @param suffix the given suffix
 * @returns The detected format or -1 if unrecognized
 * @file usr.lib/libzio/z_format_from_suffix.c
 */
extern int z_format_from_suffix (const char *suffix);

/**
 * Get the common name of a format
 * @param format The format in question
 * @returns A static string of the given common name, or null
 * @file usr.lib/libzio/z_name_from_format.c
 */
extern const char *z_name_from_format (int format);

/**
 * Get the format based on the given common name
 * @param name the given common name
 * @returns The detected format or -1 if unrecognized
 * @file usr.lib/libzio/z_format_from_name.c
 */
extern int z_format_from_name (const char *name);

/// @defgroup file functions
typedef struct zFILE zFILE;

/**
 * Open an alternative encoding file based on a file system path
 * @param path The given file system path
 * @param mode The given mode string
 * @param format The given format of the file, or -1 to auto-detect
 * @returns NULL upon error, or a new zFILE pointer to use
 * @file usr.lib/libzio/zopen.c
 */
extern zFILE *zopen (const char *restrict path, const char *restrict mode,
	int format);

/**
 * Close a file, freeing and flushing underlying data
 * @param fp The file to free
 * @retval 0 Success
 * @retval EOF an error occurred
 * @file usr.lib/libzio/zclose.c
 */
extern int zclose (zFILE *fp);

/**
 * Flush the underlying data of a file
 * @param fp The file to flush
 * @retval 0 Success
 * @retval EOF an error occurred
 * @file usr.lib/libzio/zflush.c
 */
extern int zflush (zFILE *fp);

/**
 * Lock a file
 * @param fp The file in question
 * @file usr.lib/libzio/zlockfile.c
 */
extern void zlockfile (zFILE *fp);

/**
 * Unlock a file
 * @param fp The file in question
 * @file usr.lib/libzio/zunlockfile.c
 */
extern void zunlockfile (zFILE *fp);

/**
 * Attempt to lock a file
 * @param fp The file in question
 * @retval 0 The lock was obtained
 * @retval !0 The locking failed
 * @file usr.lib/libzio/ztrylockfile.c
 */
extern int ztrylockfile (zFILE *fp);

/**
 * User locking read
 * @param fp The file to read from
 * @returns The next byte the file, or EOF
 * @file usr.lib/libzio/zgetc_unlocked.c
 */
extern int zgetc_unlocked (zFILE *fp);

/**
 * User locking write
 * @param c The byte to write
 * @param fp The file to write to
 * @returns The byte written or EOF
 * @file usr.lib/libzio/zputc_unlocked.c
 */
extern int zputc_unlocked (int c, zFILE *fp);

/**
 * Read a number of bytes from a file
 * @param buf The buffer to read into
 * @param size The size of each element to read
 * @param n The number of elements to read
 * @param fp The file to read from
 * @returns The number of elements read
 * @file usr.lib/libzio/zread.c
 */
extern size_t zread (void *restrict buf, size_t size, size_t n,
	zFILE *restrict fp);

/**
 * Write a number of bytes to a file
 * @param buf The buffer to write from
 * @param size The size of each element to write
 * @param n The number of elements to write
 * @param fp The file to write to
 * @returns The number of elements written
 * @file usr.lib/libzio/zwrite.c
 */
extern size_t zwrite (void *restrict buf, size_t size, size_t n,
	zFILE *restrict fp);

/**
 * Test for file error
 * @param fp The file to test
 * @returns Non-zero if the error indicator is set
 * @file usr.lib/libzio/zerror.c
 */
extern int zerror (zFILE *fp);

/**
 * Test for end of file
 * @param fp The file to test
 * @returns Non-zero if the end-of-file indicator is set
 * @file usr.lib/libzio/zeof.c
 */
extern int zeof (zFILE *fp);

/**
 * Clear the error and eof indicator
 * @param fp The file to clean
 * @file usr.lib/libzio/zclearerr.c
 */
extern void zclearerr (zFILE *fp);

/**
 * Stat a file
 * @note The returned data may be dependent on the underlying file system
 * @param fp The file to stat
 * @param statbuf The buffer to file
 * @returns True on error
 * @file usr.lib/libzio/zstat.c
 */
extern int zstat (zFILE *restrict fp, struct stat *statbuf);

/**
 * Change the ownership of a file
 * @note The underlying file system may be changed by this function
 * @param fp The file to change
 * @param user The user to change to
 * @param group The group to change to
 * @returns -1 upon error and zero upon success
 * @file usr.lib/libzio/zchown.c
 */
extern int zchown (zFILE *fp, uid_t user, gid_t group);

/**
 * Change the mode of a file
 * @note The underlying file system may be changed by this function
 * @param fp The file to change
 * @param mode The mode to change to
 * @returns -1 upon error and zero upon success
 * @file usr.lib/libzio/zchmod.c
 */
extern int zchmod (zFILE *fp, mode_t mode);

/**
 * Change the access and modification times of a file
 * @note The underlying file system may be changed by this function
 * @param fp The file to change
 * @param t Access time, modification time
 * @returns -1 upon error and zero upon success
 * @file usr.lib/libzio/zutimens.c
 */
extern int zutimens (zFILE *fp, struct timespec t[2]);

/**
 * Attempt to set the amount of cores used to decode/encode a file
 * @param fp The file to change
 * @param cores The cores in question
 * @returns True upon error
 * @file usr.lib/libzio/z_set_cores.c
 */
extern int z_set_cores (zFILE *fp, int cores);

/**
 * Attempt to save the original name of the file
 * @param fp The file to save it to
 * @param name The name to save
 * @returns True upon error
 * @file usr.lib/libzio/z_set_original_name.c
 */
extern int z_set_original_name (zFILE *restrict fp, const char *restrict name);

/**
 * Attempt to retrieve the original name of the file
 * @param fp The file to pull from
 * @returns The original file name, or NULL upon error
 * @file usr.lib/libzio/z_get_original_name.c
 */
extern const char *z_get_original_name (zFILE *fp);

/**
 * Attempt to set the generic compression level
 * @param fp The file to set
 * @param level The level to set it to
 * @returns True upon error
 * @file usr.lib/libzio/z_set_compression_level.c
 */
extern int z_set_compression_level (zFILE *fp, int level);

/**
 * Attempt to get the generic compression level
 * @param fp The file to get from
 * @returns The compression level, or -1
 * @file usr.lib/libzio/z_get_compression_level.c
 */
extern int z_get_compression_level (zFILE *fp);

/**
 * Attempt to set the max codeword bits
 * @param fp The file to set
 * @param bits The bits to set it to
 * @returns True upon error
 * @file usr.lib/libzio/z_set_codeword_bits.c
 */
extern int z_set_codeword_bits (zFILE *fp, int bits);

/**
 * Attempt to get the max codeword bits
 * @param fp The file to get from
 * @returns The max codeword bits, or -1
 * @file usr.lib/libzio/z_get_codeword_bits.c
 */
extern int z_get_codeword_bits (zFILE *fp);

#endif
