#ifndef __ARGS_H__
#define __ARGS_H__
#include <stdio.h>

/**
 * The command-line argment parser
 * @param argc The argument count
 * @param argv The argument values
 * @file args/args.c
 */
extern void args (int argc, char *argv[]);

/**
 * Add a new input file
 * @file args/addFile.c
 * @param path The path to the file to add
 */
extern void args_addFile (const char *path);

enum args_fileType
{
	ARGS_FILE_TYPE_C,
	ARGS_FILE_TYPE_I,
	ARGS_FILE_TYPE_IR,
	ARGS_FILE_TYPE_S,
	ARGS_FILE_TYPE_O,
	ARGS_FILE_TYPE_SO,
	ARGS_FILE_TYPE_A
};

/// @brief An input file
struct args_file
{
	enum args_fileType type;
	const char *path; // do not free
	FILE       *fp;
};

/**
 * The input files
 * @file args/addFile.c
 */
extern struct args_file *args_file;
extern int               args_files;

struct args_flags
{
	unsigned int preprocess_only : 1;
	unsigned int freestanding    : 1;

	const char *outfile;
};

/**
 * The argument flags
 * @file args/args.c
 */
extern struct args_flags args_flags;

/**
 * Free the input file list
 * @file args/freeFiles.c
 */
extern void args_freeFiles (void);

/**
 * Add a new user defined include path
 * @param path The path
 * @param mayfail May fail to open
 * @file args/addInclude.c
 */
extern void args_addInclude (const char *path, int mayfail);

struct args_include
{
	int fd;
};

/**
 * The include files
 * @file args/addInclude.c
 */
extern struct args_include *args_include;
extern int                  args_includes;

/**
 * Free the include paths
 * @file args/freeIncludes.c
 */
extern void args_freeIncludes (void);

#endif
