#include <stdio.h>
#include <string.h>
#include <nl_types.h>

nl_catd __errno_catd;

void
__init_string (void)
{
    __errno_catd = catopen("errno", 0);
}

void
__fini_string (void)
{
    catclose(__errno_catd);
}
