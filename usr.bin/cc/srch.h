#ifndef __SRCH_H__
#define __SRCH_H__

struct srch_elem
{
	int sibling;
	int child;

	void *dat;

	int   prefixsz;
	char *prefix;
};

struct srch
{
	int sz;
	int cp;

	struct srch_elem *elems;
};

#define SRCH_NULL ((struct srch){ .sz = 0, .cp = 0, .elems = NULL })

/**
 * Add a new named search element
 * @param srch The srch struct
 * @param name the element name
 * @param dat The **malloc** data (will be freed with the search struct)
 * @note dat with be freed if this fails
 * @file srch/add.c
 */
extern void srch_add (struct srch *srch, const char *name, void *dat);

/**
 * Free a search structure
 * @param srch The srch structure
 * @file srch/free.c
 */
extern void srch_free (struct srch *srch);

/**
 * Debug print a search structure
 * @param s The srch structure
 * @file srch/list.c
 */
extern void srch_list (struct srch *s);

#endif
