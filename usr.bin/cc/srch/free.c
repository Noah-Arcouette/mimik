#include "../srch.h"
#include <stdlib.h>
#include <stdio.h>

void
srch_free (struct srch *srch)
{
	// srch_list(srch);

	for (int i = 0; i<srch->sz; i++)
	{
		struct srch_elem *e = &srch->elems[i];
		free(e->prefix);
		free(e->dat);
	}
	free(srch->elems);
	srch->cp = 0;
	srch->sz = 0;
	srch->elems = NULL;
}
