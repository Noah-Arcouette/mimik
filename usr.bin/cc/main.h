#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * The program invocation name
 * @file main.c
 */
extern const char *self;

/**
 * The amount of error encountered
 * @file main.c
 */
extern long errors;

/**
 * Compile C files to IR
 * @file compileCFiles.c
 */
extern void compileCFiles (void);

#endif
