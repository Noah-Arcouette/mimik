#include <stdio.h>
#include "defs.h"

int
setVar (struct variable *dst, struct value a)
{
	if (!dst) // no variable
	{
		fprintf(stderr, "%s:%zu: Variable `%s' does not exist.\n", filename, lineno, dst->name);
		return 1;
	}

	// if value is already a variable
	if (a.variable)
	{
		dst->delta = (size_t)a.value; // set delta
	}
	else
	{
		if (compromiseTypes(NULL, a.type, dst->type))
		{
			return 1;
		}

		fputc('\t', fout);
		printType(fout, dst->type);

		fprintf(fout, " %%%zu = ", temps++);

		printValue(a);
		fputc('\n', fout);

		// assign destination to a variable
		dst->delta = temps-1;
	}

	return 0;
}
