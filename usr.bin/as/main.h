#ifndef __MAIN_H__
#define __MAIN_H__

/// @brief The command line argument options
extern struct arguments
{
	const char *outputfile;
} arguments;

/**
 * Parse the command line arguments
 * @param argc The argument count
 * @param argv The argument values
 * @returns True if an error occurred
 * @file args.c
 */
extern int args (int argc, char *argv[]);

#endif
