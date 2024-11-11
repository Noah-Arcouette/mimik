#include "defs.h"

int
compromiseTypes (struct type *d, struct type a, struct type b)
{
    // voids cannot compromise
    if (a.base == TYPE_VOID || b.base == TYPE_VOID)
    {
        goto fail;
    }

    if (!d)
    {
        return 0;
    }

    d->base = a.base>b.base?a.base:b.base; // max(a, b)
    return 0;
fail:
	fprintf   (stderr, "%s:%zu: Failed to compromise between type `", filename, lineno);
	printCType(stderr, a);
	fprintf   (stderr, "' and `");
	printCType(stderr, b);
	fprintf   (stderr, "'\n");
	return 1;
}
