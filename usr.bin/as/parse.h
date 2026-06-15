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

#ifdef X86_16
/**
 * Consume and emit an x86-16 instructions
 * @returns True if consumed
 * @file x86_16/parse.c
 */
extern int parse_x86_16 (void);
#endif

#endif
