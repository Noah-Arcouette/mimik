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

#endif
