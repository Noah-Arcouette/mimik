#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

struct info *info = (struct info *)NULL;

void
pushInfo ()
{
	// save tail
	struct info *tail = info;

	// allocate new info
	info = (struct info *)malloc(sizeof(struct info));
	if (!info)
	{
		info = tail;
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}

	// copy over data
	info->start = labelTemp++;
	info->end   = labelTemp++;
	info->elif  = labelTemp++;
	info->parent = tail;
}

void
popInfo (void)
{
	if (!info) // no information on stack
	{
		fprintf(stderr, "%s:%zu: Attempting to pop information without any on stack.\n", filename, lineno);
		exit(1);
	}

	struct info *tail = info->parent;
	free(info);
	info = tail;
}

void
freeInfo (void)
{
	struct info *tail; // preserve tail/parent
	while (info) // while there's information on the stack
	{
		tail = info->parent; // save
		free(info); // free
		info = tail; // pop
	}
}
