#ifndef __MAIN_H__
#define __MAIN_H__
#include <stddef.h>
#include <mio.h>

/**
 * The amount of error encounter
 * @file main.c
 */
extern long errors;

/**
 * The program name
 * @file main.c
 */
extern const char *self;

/**
 * Parse the command line arguments
 * @param argc The argument count
 * @param argv The argument values
 * @file args.c
 */
extern void args (int argc, char *argv[]);

/**
 * The parsed arguments
 * @file args.c
 */
#define ARG_FLAGS_DONT_MAP 1 // Don't create a map (-r)
extern int argFlags; // The argument flags
extern const char *outputFile; // the output file
extern const char *scriptFile; // the script file

#ifdef STRIP
extern char *stripcmd; // the strip command, must be freed
#endif

/**
 * Open an input file and load it into the input list
 * @param path The file path
 * @file openInputFile.c
 */
extern void openInputFile (const char *path);

struct inputFile
{
	const char *path; // not allocated

	struct MiO_Gap *gap;
	long            gaps;

	struct MiO_Symbol *symbol;
	long               symbols;

	void *data;
	long  size;
};

/**
 * The input object files
 * @file openInputFile.c
 */
extern struct inputFile *input;
extern long              inputs;

/**
 * Close all input files
 * @file closeInputFiles.c
 */
extern void closeInputFiles (void);

/**
 * Merge input architectures together
 * @file mergeArchitecture.c
 * @param path The file name path
 * @param arch The architecture to merge
 */
extern void mergeArchitecture (const char *path, const struct MiO_Arch *arch);

/**
 * The architecture section of the output file
 * @file mergeArchitecture.c
 */
extern struct MiO_Arch outputArch;

/**
 * The linker script parser
 * @file linker.c
 */
extern void linker (void);

/**
 * Set the entry point name
 * @param name The name to set it to
 * @file entry.c
 */
extern void setEntry (const char *name);

/**
 * Emit data to the output file
 * @param buf The data to emit
 * @param amt The amount of data emit
 * @file emit.c
 */
extern void emit (void *buf, long amt);

/**
 * The main output file data buffer
 * @file emit.c
 */
extern void *outputBuf;
extern long  outputsz;

/**
 * Emit the entry section into the output buffer
 * @file entry.c
 */
extern void emitEntrySection (void);

/**
 * Emit the architecture section into the output buffer
 * @file emitArchSection.c
 */
extern void emitArchSection (void);

/**
 * Rename static symbols
 * @file renameStaticSymbols.c
 */
extern void renameStaticSymbols (void);

/**
 * Check for double definitions of global symbols
 * @file checkGlobalSymbols.c
 */
extern void checkGlobalSymbols (void);

/**
 * Find an input symbol
 * @param name The symbol to find
 * @returns NULL or a pointer to the symbol
 */
extern struct MiO_Symbol *findSymbol (const char *name);

/**
 * The output symbols
 * @file newSymbol.c
 */
extern struct MiO_Symbol *outputSymbol;
extern size_t             outputSymbolsz;
extern size_t             outputSymbolcp;

/**
 * Create a new output symbol
 * @param val the symbols value
 * @param size The symbols size
 * @param type The symbols type and flags
 * @param name The name of the symbol
 * @file newSymbol.c
 */
extern void newSymbol (int64_t val, long size, int type, const char *name);

/**
 * Free the symbols buffer
 * @file freeSymbols.c
 */
extern void freeSymbols (void);

/**
 * Emit symbols to the output buffer
 * @file emitSymbols.c
 */
extern void emitSymbols (void);

/**
 * The maps section data
 * @file newMap.c
 */
extern struct MiO_Map *outputMap;
extern long            outputMaps;

/**
 * Add a new map to the output
 * @param map The map to add
 * @file newMap.c
 */
extern void newMap (const struct MiO_Map *map);

/**
 * Write maps to the output buffer
 * @file emitMaps.c
 */
extern void emitMaps (void);

/**
 * Free the maps data
 * @file freeMaps.c
 */
extern void freeMaps (void);

/**
 * Find and emit/reserve the given section(s) from the given file(s)
 * @file dumpSection.c
 * @param file The file name
 * @param section The section name
 */
extern void dumpSection (const char *file, const char *section);
/**
 * Add data to the data reserve
 * @file reserve.c
 * @param amt The amount to reserve
 */
extern void reserve (long amt);

/**
 * The virtual data section size
 * @file reserve.c
 */
extern long virtualsz;

#endif
