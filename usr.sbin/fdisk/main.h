#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>

/**
 * The program name
 * @file main.c
 */
extern const char *self;

/**
 * Open the input disk file
 * @param argc The argument count
 * @param argv The argument values
 * @returns True upon error
 * @file openDisk.c
 */
extern int openDisk (int argc, char *argv[]);

/**
 * The disk file
 * @file openDisk.c
 */
extern FILE *disk;

/**
 * The disk size
 * @file openDisk.c
 */
extern size_t diskSize;

/**
 * If an error occurred
 * @file main.c
 */
extern long errors;

#endif
