#include "../srch.h"
#include <libintl.h>
#include <stdio.h>

static void
_list (struct srch *s, struct srch_elem *e, int depth)
{
	// depth
	for (int i = 0; i<depth; i++)
	{
		fprintf(stderr, "\t");
	}

	// prefix
	fprintf(stderr, "-`%.*s'\n", e->prefixsz, e->prefix);
	if (e->child > 0)
	{
		_list(s, &s->elems[e->child], depth+1);
	}
	if (e->sibling > 0)
	{
		_list(s, &s->elems[e->sibling], depth);
	}
}

void
srch_list (struct srch *s)
{
	if (s->sz)
	{
		_list(s, s->elems, 0);
	}
}
