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

/**
 * The archflag set macro
 * @returns True if consumed
 * @file parse/archflag.c
 */
extern int parse_archflag (void);

/**
 * The sys set macro
 * @returns True if consumed
 * @file parse/sys.c
 */
extern int parse_sys (void);

/**
 * The usys set macro
 * @returns True if consumed
 * @file parse/usys.c
 */
extern int parse_usys (void);

/**
 * The sysflag set macro
 * @returns True if consumed
 * @file parse/sysflag.c
 */
extern int parse_sysflag (void);

#endif
