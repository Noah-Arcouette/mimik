#include <stdio.h>
#include "defs.h"

int
expr (struct value *dst, struct value a, struct value b, const char *operation)
{
    if (compromiseTypes(&dst->type, a.type, b.type))
    {
        fprintf  (stderr, "%s:%zu: Failed to compromise between type `", filename, lineno);
        printType(stderr, a.type);
        fprintf  (stderr, "' and `");
        printType(stderr, b.type);
        fprintf  (stderr, "'\n");
        
        return 1;
    }

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

