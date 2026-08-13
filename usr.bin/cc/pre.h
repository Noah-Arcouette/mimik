#ifndef __PRE_H__
#define __PRE_H__
#include "lex.h"

/**
 * Update the lexer token, after preprocessing
 * @file pre/preproc.c
 */
extern void preproc (void);

/**
 * Parse a directive
 * @note this is called right after the hash is consumed
 * @file pre/directive.c
 */
extern void pre_directive (void);

/**
 * Parse an include directive
 * @file pre/include.c
 */
extern void pre_include (void);

/**
 * Attempt to find an included file
 * @param path The include name
 * @param searchLocal Search the current directory
 * @file lex/findInclude.c
 * @returns NULL or an allocated file path to the included file
 */
extern char *pre_findInclude (const char *path, int searchLocal);

#endif
