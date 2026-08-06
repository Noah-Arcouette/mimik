#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <mbr.h>

/**
 * The disk geometry
 * @file main.c
 */
extern int bytesPerSector;
extern int sectorsPerCylinder;
extern int cylindersPerHead;
extern int heads;

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

/**
 * Set boot code of the partition map
 * @file setBootCode.c
 * @param path The path to the boot code
 */
extern void setBootCode (const char *path);

/**
 * Update CHS values
 * @file updateCHS.c
 */
extern void updateCHS (void);

/**
 * List the partition information
 * @file listParts.c
 */
extern void listParts (void);

/**
 * Print a size
 * @file printSize.c
 * @param val The sized value to print
 */
extern void printSize (unsigned long val);

/// @defgroup MBR support
/**
 * Enter the MBR
 * @param load Load it or not
 * @param try Only try to enter the table
 * @file mbr/enterTable.c
 */
extern void mbr_enterTable (int load, int try);

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

/**
 * Set boot code of the MBR
 * @file mbr/setBootCode.c
 * @param path The path to the boot code
 * @param size The bootcode size
 */
extern void mbr_setBootCode (const char *path, size_t size);

/**
 * Write the MBR partition info to disk
 * @file mbr/commit.c
 */
extern void mbr_commit (void);

/**
 * Update CHS values
 * @file mbr/updateCHS.c
 */
extern void mbr_updateCHS (void);

/**
 * List the partition information
 * @file mbr/listParts.c
 */
extern void mbr_listParts (void);

#endif
