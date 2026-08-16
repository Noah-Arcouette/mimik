#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <mbr.h>

/**
 * Load the VBR
 * @file start.c
 */
extern [[noreturn]] void _start (void);

/**
 * Attempt to find the active MBR partition
 * @file find_mbr_partition.c
 * @returns NULL or the first active MBR partition
 */
extern struct mbr_part *find_mbr_partition (void);

/**
 * The first mbr partition
 * @file linker.ld
 */
extern struct mbr_part *MBR_PART1;

/**
 * Halt the processor
 * @file halt.c
 */
extern [[noreturn]] void halt (void);

/**
 * Print a string
 * @param s The string
 * @file puts.c
 */
extern void puts (const char *s);

/**
 * The disk number
 * @file init.s
 */
extern char diskNumber;

#endif
