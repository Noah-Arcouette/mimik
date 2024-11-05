#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct node *
addNode (struct node *restrict parent, const struct node *restrict child)
{
	if (!child)
	{
		return (struct node *)NULL;
	}

	struct node *copy = (struct node *)malloc(sizeof(struct node));
	if (!copy)
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
	memcpy(copy, child, sizeof(struct node)); // hard copy, be careful nested pointers will not copy over

	// add to list
	if (parent->last)
	{
		parent->last->next = copy;
	}
	else
	{
		parent->child = copy; // if no last then add to start and end (the only node)
	}
	parent->last = copy;
	return copy;
}

struct node *
attachNode (struct node *restrict parent, const struct node *restrict sibling)
{
	if (!sibling->nodeType)
	{
		return (struct node *)NULL;
	}

	struct node *copy = (struct node *)malloc(sizeof(struct node));
	if (!copy)
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
	memcpy(copy, sibling, sizeof(struct node)); // hard copy, be careful nested pointers will not copy over

	struct node **last = &parent->next;

	while (*last) // goto last, NULL, sibling
	{
		last = &(*last)->next;
	}

	*last = copy; // set to the copy

	return copy;
}
