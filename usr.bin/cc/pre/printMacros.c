#include "../pre.h"
#include <libintl.h>
#include <math.h>

static int _maxDepth;

static void
_printMacros (int idx, int depth)
{
	if (depth > _maxDepth) _maxDepth = depth;

	for (int i = 0; i<depth; i++)
	{
		fprintf(stderr, "\t");
	}

	if (idx < 0)
	{
		fprintf(stderr, "-\n");
	}
	else
	{
		struct pre_macro *m = &pre_macro[idx];

		fprintf(stderr, "-`%s' : `%s'\n", m->name, m->value);
		_printMacros(m->left, depth+1);
		_printMacros(m->right, depth+1);
	}
}

void
pre_printMacros (void)
{
	_maxDepth = 0;
	_printMacros(pre_macroRoot, 0);

	fprintf(stderr, gettext(
"Max depth     : %d\n"
"Macro #       : %d\n"),
		_maxDepth, pre_macros);
}
