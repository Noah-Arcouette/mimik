#ifndef __PRE_H__
#define __PRE_H__
#include "srch.h"
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
 * Parse a define directive
 * @file pre/define.c
 */
extern void pre_define (void);

/**
 * Attempt to find an included file
 * @param path The include name
 * @param searchLocal Search the current directory
 * @file lex/findInclude.c
 * @returns NULL or an allocated file path to the included file
 */
extern char *pre_findInclude (const char *path, int searchLocal);

/**
 * The macros
 * @param name The name of the macro
 * @param value The value of the macro
 * @file pre/addMacro.c
 */
extern void pre_addMacro (const char *name, const char *value);

/**
 * The given macros
 * @file pre/addMacro.c
 */
extern struct srch pre_macro;

#endif
