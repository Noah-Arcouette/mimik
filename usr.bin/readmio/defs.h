#ifndef __DEFS_H__
#define __DEFS_H__
#include <mio.h>
#include <stdio.h>

// readmio.c
extern const char *self;

// printError.c
extern void printError (int, const char *, ...);

// printmio.c, print a mio file information
extern void printMiO (FILE *);

// printHeader.c
extern void printHeader (struct MiO_Header);

#endif
