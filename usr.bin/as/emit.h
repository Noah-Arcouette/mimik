#ifndef __EMIT_H__
#define __EMIT_H__
#include <mio.h>

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

#endif
