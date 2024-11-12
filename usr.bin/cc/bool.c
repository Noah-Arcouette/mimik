#include <stdio.h>
#include "defs.h"

int
boolExpr (struct value *dst, struct value a, struct value b, const char *operation)
{
	struct type c; // compromised type
	if (compromiseTypes(&c, a.type, b.type))
	{
		return 1;
	}
	dst->type.base = TYPE_BOOL;

	fputc('\t', fout);
	printType(fout, dst->type);

	fprintf(fout, " %%%zu = %s_", temps++, operation); // bool var = op_type params

	printType (fout, c);
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
