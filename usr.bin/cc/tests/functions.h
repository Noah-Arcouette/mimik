#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <mbr.h>

/**
 * Display a message and halt forever
 * @file halt.s
 **/
extern [[noreturn]] void halt (void);

/**
 * Initialize registers and relocate MBR
 * @file init.s
 **/
extern [[noreturn]] void _init (void);

/**
 * The disk number upon boot
 * @file init.s
 **/
extern char diskNumber;

/**
 * The page number upon boot
 * @file init.s
 **/
extern char pageNumber;

/**
 * Find the bootable partition, load it, and jump to it
 * @file start.s
 **/
extern [[noreturn]] void _start (void);

/**
 * Attempt to find a bootable partition inside the MBR
 * @returns (in %ax) a pointer to the bootable partition, or zero if not found
 * @file find_mbr_partition.s
 */
extern struct mbr_part *find_mbr_partition (void);

/**
 * Print a string
 * @param ax The string
 * @file puts.s
 */
extern void puts (const char *ax);

#endif
