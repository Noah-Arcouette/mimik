#include "../pre.h"
#include <stdlib.h>

void
pre_freeMacros (void)
{
	// pre_printMacros();

	for (int i = 0; i<pre_macros; i++)
	{
		struct pre_macro *m = &pre_macro[i];

		free(m->value);
		free(m->name);
	}
	free(pre_macro);
	pre_macro     = NULL;
	pre_macros    = 0;
	pre_macroRoot = -1;
}
