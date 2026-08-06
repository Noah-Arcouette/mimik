#error "this is only for documentational purposes"

/**
 * Display a message and halt forever
 * @file stage1/halt.s
 **/
extern void _Noreturn halt (void);

/**
 * Initialize registers
 * @file stage1/init.s
 **/
extern void _Noreturn _init (void);

/**
 * The disk number upon boot
 * @file stage1/init.s
 **/
extern char diskNumber;

/**
 * The page number upon boot
 * @file stage1/init.s
 **/
extern char pageNumber;

/**
 * Load stage2
 * @file stage1/start.s
 **/
extern void _Noreturn _start (void);

/**
 * Print a string
 * @param si The string
 * @file stage1/puts.s
 */
extern void puts (const char *si);
