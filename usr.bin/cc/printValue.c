#include "defs.h"
#include <stdio.h>

void
printValue (struct value v)
{
	if (v.variable)
	{
		fprintf(fout, "%%%zu", (size_t)v.value);
		return;
	}

	switch (v.type.base)
	{
	case TYPE_VOID:
		fprintf(fout, "(void)");
		break;
	case TYPE_BOOL:
		fprintf(fout, "%d", (int)v.value&1);
		break;
	case TYPE_INT:
		fprintf(fout, "%d", (int)v.value);
		break;
	}
}

