#include <stdio.h>
#include "defs.h"

enum dataTypes dataTypes = DATA_TYPE_ILP32;

void
printType (FILE *f, struct type t)
{
    switch (t.base)
    {
        case TYPE_INT:
            switch (dataTypes)
            {
            case DATA_TYPE_ILP32:
                fprintf(f, "i32");
                break;
            }
            break;
        case TYPE_VOID:
            fprintf(f, "void");
            break;
    }
}
