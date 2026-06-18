#ifndef __MAIN_H__
#define __MAIN_H__

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

#endif
