#ifndef __PARSE_H__
#define __PARSE_H__

/**
 * Attempt to consume a section
 * @returns True if a section was consumed
 * @file parse/section.c
 */
extern int parse_section (void);

/**
 * Attempt to consume an architecture
 * @returns True if an architecture was consumed
 * @file parse/architecture.c
 */
extern int parse_architecture (void);

/**
 * Attempt to consume a label
 * @returns True if a label was consumed
 * @file parse/label.c
 */
extern int parse_label (void);

/**
 * Attempt to consume a global directive
 * @returns True if a global directive was consumed
 * @file parse/global.c
 */
extern int parse_global (void);

/**
 * Attempt to consume a number
 * @param val The value of the number, or NULL
 * @returns True if consumed
 * @file parse/number.c
 */
extern int parse_number (long *val);

/**
 * Attempt to consume a reservation directive
 * @returns True if consumed
 * @file parse/reserve.c
 */
extern int parse_reserve (void);

#ifdef X86_16
/**
 * Consume and emit an x86-16 instructions
 * @returns True if consumed
 * @file x86_16/parse.c
 */
extern int parse_x86_16 (void);
#endif

#endif
