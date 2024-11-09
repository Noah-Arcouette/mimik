#include <stdio.h>
#include "defs.h"

int
setVar (struct variable *dst, struct value a)
{
    if (compromiseTypes(NULL, a.type, dst->type))
    {
        fprintf  (stderr, "%s:%zu: Failed to compromise between type `", filename, lineno);
        printType(stderr, a.type);
        fprintf  (stderr, "' and `");
        printType(stderr, dst->type);
        fprintf  (stderr, "'\n");

        return 1;
    }

    fputc('\t', fout);
    printType(fout, dst->type);

    fprintf(fout, " %%%zu = ", temps++);

    printValue(a);
    fputc('\n', fout);

    // assign destination to a variable
    dst->delta = temps-1;

    return 0;
}
