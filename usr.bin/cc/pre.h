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

#endif
