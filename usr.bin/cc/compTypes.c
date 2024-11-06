#include "defs.h"

int
compromiseTypes (struct type *d, struct type a, struct type b)
{
    // voids cannot compromise
    if (a.base == TYPE_VOID || b.base == TYPE_VOID)
    {
        return 1;
    }

    if (!d)
    {
        return 0;
    }

    d->base = a.base>b.base?a.base:b.base; // max(a, b)
    return 0;
}
