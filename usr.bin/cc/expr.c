#include <stdio.h>
#include "defs.h"

int
expr (struct value *dst, struct value a, struct value b, const char *operation)
{
	if (compromiseTypes(&dst->type, a.type, b.type))
	{
		return 1;
	}

	fputc('\t', fout);
	printType(fout, dst->type);

	fprintf(fout, " %%%zu = %s_", temps++, operation);

	printType (fout, dst->type);
	fputc(' ', fout);

	printValue(a);
	fputc(' ', fout);

	printValue(b);
	fputc('\n', fout);

	// assign destination to a variable
	dst->variable = 1;
	dst->value    = temps-1;

	return 0;
}

