#ifndef __DEFS_H__
#define __DEFS_H__
#include <stddef.h>
#include <stdio.h>
#include <mio.h>

// readmio.c
extern const char *self;

// printError.c
extern void printError (int, const char *, ...);

// printmio.c, print a mio file information
extern struct MiO_Header currentHeader;
extern void printMiO (FILE *);

// printHeader.c
extern void printHeader (struct MiO_Header);

// printSection.c
extern void printSection (FILE *, struct MiO_Section);

// printData.c
extern void printData (struct MiO_Data);

// printLibraries.c
extern void printLibraries (FILE *, struct MiO_Section);

// printSymbolList.c
extern void printSymbolList (FILE *, struct MiO_Section);

// printGaps.c
extern void printGaps (FILE *, struct MiO_Section);

// printMap.c
extern void printMap (FILE *, struct MiO_Section);

// printSeg.c
extern void printSeg (FILE *, struct MiO_Section);

// dataStart.c
extern size_t dataStart;
extern void   getDataStart (FILE *fp);

#endif
