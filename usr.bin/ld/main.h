#ifndef __MAIN_H__
#define __MAIN_H__
#include <mio.h>

/**
 * The amount of error encounter
 * @file main.c
 */
extern long errors;

/**
 * The program name
 * @file main.c
 */
extern const char *self;

/**
 * Parse the command line arguments
 * @param argc The argument count
 * @param argv The argument values
 * @file args.c
 */
extern void args (int argc, char *argv[]);

/**
 * The parsed arguments
 * @file args.c
 */
#define ARG_FLAGS_DONT_MAP 1 // Don't create a map (-r)
extern int argFlags; // The argument flags
extern const char *entry; // The entry symbol
extern const char *outputFile; // the output file
extern const char *scriptFile; // the script file

/**
 * Open an input file and load it into the input list
 * @param path The file path
 * @file openInputFile.c
 */
extern void openInputFile (const char *path);

struct inputFile
{
	const char *path; // not allocated

	struct MiO_Gap *gap;
	long            gaps;

	struct MiO_Symbol *symbol;
	long               symbols;

	void *data;
	long  size;
};

/**
 * The input object files
 * @file openInputFile.c
 */
extern struct inputFile *input;
extern long              inputs;

/**
 * Close all input files
 * @file closeInputFiles.c
 */
extern void closeInputFiles (void);

/**
 * Merge input architectures together
 * @file mergeArchitecture.c
 * @param path The file name path
 * @param arch The architecture to merge
 */
extern void mergeArchitecture (const char *path, const struct MiO_Arch *arch);

/**
 * Find conflicting symbols, if they're static then rename them,
 * if they're global then crash
 * @file resolveConflictSymbols.c
 */
extern void resolveConflictSymbols (void);

/**
 * The linker script parser
 * @file linker.c
 */
extern void linker (void);

#endif
