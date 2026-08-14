#include "../srch.h"
#include <string.h>

static void *
_find (const struct srch *srch, const struct srch_elem *e, const char *name)
{
	int namesz = strlen(name)+1;

	// amount of matching characters
	int matches = 0;
	for (int i = 0; ; i++)
	{
		if (i >= e->prefixsz) break;
		if (i >= namesz) break;

		if (e->prefix[i] != name[i]) break;

		matches++;
	}

	if (matches == namesz) // found it
	{
		return e->dat;
	}
	else if (matches == e->prefixsz) // move down a level
	{
		if (e->child >= 0)
		{
			return _find(srch, &srch->elems[e->child], name+matches);
		}
		return NULL;
	}
	else if (!matches) // no match try sibling
	{
		if (e->sibling >= 0)
		{
			return _find(srch, &srch->elems[e->sibling], name);
		}
		return NULL;
	}
	else return NULL; // partial match is not possible
}

void *
srch_find (const struct srch *srch, const char *name)
{
	if (!srch->sz) return NULL;

	return _find(srch, srch->elems, name);
}
