#include "./stdio/stdio.h"
#include <stdlib.h>

int main (void);

void
_start (void)
{
    __init_stdio();

    exit(main());
}
