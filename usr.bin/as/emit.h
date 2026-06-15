#ifndef __EMIT_H__
#define __EMIT_H__
#include <mio.h>

/**
 * The offset into emitbuf where the current section is, or negative if not in a
 * section
 * @file emit/section.c
 */
extern long currentSection;

/**
 * Enter a new section
 * @file emit/section.c
 * @param name The name of the new section to create
 */
extern void emitSection (const char *name);

/**
 * Enter a new symbol
 * @file emit/symbol.c
 * @param name The name of the new symbol to create
 */
extern void emitSymbol (const char *name);

/**
 * Emit symbol data into the output stream
 * @file emit/symbol.c
 */
extern void emitSymbolData (void);

/**
 * The current symbol flags
 * @file emit/symbol.c
 */
extern int symbolFlags;

/**
 * The current symbol we're in, offset into *symbol* or negative
 * @file emit/symbol.c
 */
extern long currentSymbol;

/**
 * The symbol buffer
 * @file emit/symbol.c
 */
extern struct MiO_Symbol *symbol;

/**
 * Current offset of the virtual data region
 * @file emit/reserve.c
 */
extern long virtualOffset;

/**
 * The raw buffer of the output file
 * @file emit.c
 */
extern char *emitbuf;
extern long  emitsz;

/**
 * Free the emit buffer
 * @file emit.c
 */
extern void freeEmit (void);

/**
 * Emit a raw buffer without any other handling
 * @param buf The buffer to emit
 * @param sz The buffer size
 * @returns The offset of the start of the buffer in emitbuf
 * @returns Negative upon error
 * @file emit.c
 */
extern long emitRaw (const void *buf, long sz);

/**
 * Emit a buffer, updating section and symbol data
 * @param buf The buffer to emit
 * @param sz The buffer size
 * @returns The offset of the start of the buffer in emitbuf
 * @returns Negative upon error
 * @file emit.c
 */
extern long emit (const void *buf, long sz);

/**
 * The current architecture
 * @file arch.c
 */
extern struct MiO_Arch currentArchitecture;

/**
 * Emit the current architecture as a section
 * @file arch.c
 */
extern void emitArchitecture (void);

/**
 * Set architecture
 * @param arch The architecture to set to
 * @file setArch.c
 */
extern void setArch (const char *arch);

/**
 * Create a gap at the current offset
 * @param symbol The symbol to reference for this gap
 * @param type The type of this gap
 * @file emit/gap.c
 */
extern void emitGap (const char *symbol, int type);

/**
 * Emit gap data into the output stream
 * @file emit/gap.c
 */
extern void emitGapData (void);

#endif
