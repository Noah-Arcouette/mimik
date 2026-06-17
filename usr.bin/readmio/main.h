#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>

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

/**
 * Print out the current section seeking to the next section
 * @file printSection.c
 * @param fp The file pointer to print from
 * @param path The path to the file
 * @retval True : if there is more sections to print
 * @retval False : if there is no more sections ot print or an error occurred
 */
extern int printSection (FILE *fp, const char *path);

/**
 * Print out an architecture data section, seeking to the next section
 * @param fp The file pointer
 * @param size The size of this section
 * @file printArch.c
 */
extern void printArch (FILE *fp, unsigned long long size);

#endif
