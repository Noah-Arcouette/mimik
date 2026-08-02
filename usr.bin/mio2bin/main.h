#ifndef __MAIN_H__
#define __MAIN_H__
#include <mio.h>

/**
 * The current program name
 * @file main.c
 */
extern const char *self;

/**
 * The amount of errors encountered
 * @file main.c
 */
extern long errors;

/**
 * The input file buffer
 * @file main.c
 */
extern char *buf;
extern long  bufsz;

/**
 * Parse the input arguments
 * @param argc The argument count
 * @param argv The argument values
 * @file args.c
 */
extern void args (int argc, char *argv[]);

/**
 * The argument flags
 * @file args.c
 */
extern short argFlags;

#define LOAD_VIRTUAL 1 // load virtual maps

/**
 * The output file, or NULL if unset
 * @file args.c
 */
extern const char *outputfile;

/**
 * Read the given file into the given buffer
 * @param path The file path, or `-`
 * @param buf A pointer to a given buffer (will be reallocated)
 * @param bufsz The size of the buffer
 * @file readIn.c
 */
extern void readIn (const char *path);

/**
 * Get section information from a file
 * @file getSections.c
 */
extern void getSections (void);

/**
 * The input file's symbols
 * @file getSections.c
 */
extern struct MiO_Symbol *symbol;
extern long               symbols;

/**
 * The input file's gaps
 * @file getSections.c
 */
extern struct MiO_Gap *gap;
extern long            gaps;

/**
 * The input file's maps
 * @file getSections.c
 */
extern struct MiO_Map *map;
extern long            maps;

/**
 * Create the virtual and physical address of maps
 * @file fixMaps.c
 */
extern void fixMaps (void);

/**
 * Relocate symbols
 * @file relocateSymbols.c
 */
extern void relocateSymbols (void);

/**
 * Fill the defined gaps
 * @file fillGaps.c
 */
extern void fillGaps (void);

/**
 * Execute maps and allocate an output buffer
 * @file executeMaps.c
 */
extern void executeMaps (void);

/**
 * The output data of the loaded binary
 * @file executeMaps.c
 */
extern long  outbufsz;
extern char *outbuf;

#endif
