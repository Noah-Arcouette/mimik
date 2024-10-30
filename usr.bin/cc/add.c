#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct node *
addNode (struct node *restrict parent, const struct node *restrict child)
{
	struct node *copy = (struct node *)malloc(sizeof(struct node));
	if (!copy)
	{
		int errnum;
	memerror:
		errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
	memcpy(copy, child, sizeof(struct node)); // hard copy, be careful nested pointers will not copy over

	// copy string over
	if (child->symbol)
	{
		copy->symbol = strdup(child->symbol);
		if (!copy->symbol)
		{
			free(copy); // free up node copy
			goto memerror;
		}
	}

	// add to list
	if (parent->last)
	{
		parent->last->next = copy;
	}
	else
	{
		parent->next = copy; // if no last then add to start and end (the only other node)
	}
	parent->last = copy;
	return copy;
}
