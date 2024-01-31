#ifndef __LIB_C_NL_TYPES_H__
#define __LIB_C_NL_TYPES_H__
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

typedef FILE *nl_catd;

size_t nl_ent_index (int set, int message); // index into table

struct nl_catalogue
{
	char          magic[4]; // "MCAT"
	unsigned char rev; // 0

	size_t entries;
	struct
	{
		int    set;
		int    message;
		off_t  index; // into data
	} table[];
};

// nls/catopen.c
nl_catd catopen (const char *name, int flags);

// nls/catclose.c
int catclose (nl_catd);

// nls/catgets.c
char *catgets (nl_catd, int set, int message, const char *def);

#endif
