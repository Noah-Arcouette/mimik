#ifndef __ARGS_H__
#define __ARGS_H__
#include <stdio.h>

/**
 * Parse the arguments
 * @param argc The argument count
 * @param argv The argument values
 * @file args/args.c
 */
extern void args (int argc, char *argv[]);

/**
 * The output file
 * @file args/handleMachine.c
 */
extern const char *args_outputFile;

enum args_machine
{
	ARGS_MACHINE_NONE = 0,
	ARGS_MACHINE_I8086,
	ARGS_MACHINE_X86_64_GENERIC
};

/**
 * The machine architecture
 * @file args/args.c
 */
extern enum args_machine args_machine;

/**
 * Handle machine arguments
 * @file args/handleMachine.c
 * @param opt The option argument
 */
extern void args_handleMachine (const char *opt);

enum args_file_type
{
	ARGS_FILE_TYPE_C,
	ARGS_FILE_TYPE_S,
	ARGS_FILE_TYPE_O
};

struct args_file
{
	char *path;
	enum args_file_type type;
	FILE *fp;
};

/**
 * The input files
 * @file args/handleFile.c
 * @note freed by args_freeFile
 */
extern struct args_file *args_file;
extern long              args_files;

/**
 * Free the input files
 * @file args/freeFile.c
 */
extern void args_freeFile (void);

/**
 * Handle input files
 * @param name The file name
 * @file args/handleFile.c
 */
extern void args_handleFile (const char *name);

enum args_mode
{
	ARGS_MODE_DEFAULT = 0, // the default build
	ARGS_MODE_OBJECT // only build objects
};

/**
 * The output mode
 * @file args/handleMode.c
 */
extern enum args_mode args_mode;

/**
 * Handle build modes
 * @param mode The build mode
 * @file args/handleMode.c
 */
extern void args_handleMode (const char *mode);

struct args_include
{
	const char *path; // a static pointer to the include path
};

/**
 * The constant system includes
 * @file args/handleInclude.c
 */
#define ARGS_SYSTEM_INCLUDES (2l)
extern const struct args_include args_system_include[ARGS_SYSTEM_INCLUDES];
extern long                      args_system_includes;

/**
 * The user defined include paths
 * @file args/handleInclude.c
 * @note frees with args_freeInclude
 */
extern struct args_include *args_include;
extern long                 args_includes;

/**
 * Free the include paths
 * @file args/freeInclude.c
 */
extern void args_freeInclude (void);

/**
 * Handle include paths
 * @param path The include path
 * @file args/handleInclude.c
 */
extern void args_handleInclude (const char *path);

#endif
