#ifndef __PARSE_H__
#define __PARSE_H__

/**
 * The entry set macro
 * @returns True if consumed
 * @file parse/entry.c
 */
extern int parse_entry (void);

/**
 * The arch set macro
 * @returns True if consumed
 * @file parse/arch.c
 */
extern int parse_arch (void);

/**
 * The uarch set macro
 * @returns True if consumed
 * @file parse/uarch.c
 */
extern int parse_uarch (void);

#endif
