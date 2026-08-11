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

/**
 * Free the input file list
 * @file args/freeFiles.c
 */
extern void args_freeFiles (void);

#endif
