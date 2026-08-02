#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * The current program name
 * @file main.c
 */
extern const char *self;

/**
 * The amount of errors encountered
 * @file main.c
 */
extern long errors;

/**
 * The input file buffer
 * @file main.c
 */
extern char *buf;
extern long  bufsz;

/**
 * Parse the input arguments
 * @param argc The argument count
 * @param argv The argument values
 * @file args.c
 */
extern void args (int argc, char *argv[]);

/**
 * The argument flags
 * @file args.c
 */
extern short argFlags;

#define LOAD_VIRTUAL 1 // load virtual maps

/**
 * The output file, or NULL if unset
 * @file args.c
 */
extern const char *outputfile;

/**
 * Read the given file into the given buffer
 * @param path The file path, or `-`
 * @param buf A pointer to a given buffer (will be reallocated)
 * @param bufsz The size of the buffer
 * @file readIn.c
 */
extern void readIn (const char *path);

/**
 * Get section information from a file
 * @file getSections.c
 */
extern void getSections (void);

#endif
