#ifndef __MAIN_H__
#define __MAIN_H__
#include "args.h"

/**
 * The invocation name
 * @file main.c
 */
extern const char *self;

/**
 * The amount of errors encountered
 * @file main.c
 */
extern int errors;

/**
 * Emit the files after preprocessing
 * @file preprocessOnly.c
 */
extern void preprocessOnly (void);

/**
 * Compile a C file to assembler
 * @file compileCFile.c
 * @param file The file to compile
 */
extern void compileCFile (struct args_file *file);

#endif
