#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <mbr.h>

/**
 * The program name
 * @file main.c
 */
extern const char *self;

/**
 * Open the input disk file
 * @param argc The argument count
 * @param argv The argument values
 * @returns True upon error
 * @file openDisk.c
 */
extern int openDisk (int argc, char *argv[]);

/**
 * The disk file
 * @file openDisk.c
 */
extern FILE *disk;

/**
 * The disk size
 * @file openDisk.c
 */
extern size_t diskSize;

/**
 * If an error occurred
 * @file main.c
 */
extern long errors;

/**
 * Enter the given partition table
 * @param table The table to enter
 * @param load Whether or not to load the table
 * @file enterTable.c
 */
extern void enterTable (const char *table, int load);

enum partMode
{
	MODE_NONE = 0,
	MODE_MBR
};

/**
 * The current partition mode
 * @file enterTable.c
 */
extern enum partMode partMode;


/// @defgroup MBR support
/**
 * Enter the MBR
 * @param load Load it or not
 * @file mbr/enterTable.c
 */
extern void mbr_enterTable (int load);

/**
 * The mbr partition table
 * @file mbr/enterTable.c
 */
extern struct mbr mbr;

/**
 * Whether or not the MBR should be written
 * @file mbr/enterTable.c
 */
extern int writeMBR;

#endif
