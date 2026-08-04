#error "this is only for documentational purposes"

/*
ABI note:
 - functions do not preserve any registers
 - %ax is the return value if any

*/

/**
 * Display a message and halt forever
 * @file halt.s
 **/
extern void _Noreturn halt (void);

/**
 * Initialize registers and relocate MBR
 * @file init.s
 **/
extern void _Noreturn _init (void);

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
extern void _Noreturn _start (void);

/**
 * Attempt to find a bootable partition inside the MBR
 * @returns (in %ax) a pointer to the bootable partition, or zero if not found
 * @file find_mbr_partition.s
 */
extern int find_mbr_partition (void);

/**
 * Print a string
 * @param si The string
 * @file puts.s
 */
extern void puts (const char *si);
