#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * The name of the running executable
 * @file main.c
 */
extern const char *self;

/**
 * The total amount of errors
 * @file main.c
 */
extern int errors;

/**
 * Print out the given file
 * @file printFile.c
 * @param path The path to the given file
 */
extern void printFile (const char *path);

#endif
