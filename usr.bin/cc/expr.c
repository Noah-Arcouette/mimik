#include <stdio.h>
#include <string.h>
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

	fprintf(fout, " %%%zu = %s_", temps++, operation); // type var = operation_type params

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

void
unaryExpr (struct value *dst, struct value a, const char *operation)
{
	memcpy(dst, &a, sizeof(struct value));

	fputc('\t', fout);
	printType(fout, dst->type);

	fprintf(fout, " %%%zu = %s_", temps++, operation); // type var = op_type param

	printType (fout, dst->type);
	fputc(' ', fout);

	printValue(a);
	fputc('\n', fout);

	// assign destination to a variable
	dst->variable = 1;
	dst->value    = temps-1;
}

