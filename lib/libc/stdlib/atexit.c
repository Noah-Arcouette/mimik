#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <errno.h>

void (*__at_exit_funcs[ATEXIT_MAX])(void);
size_t __at_exit_amount = 0;

int 
atexit (void (*func)(void))
{
    if (__at_exit_amount >= ATEXIT_MAX)
    {
        errno = ERANGE;
        return -1;
    }

    __at_exit_funcs[__at_exit_amount++] = func;
    return 0;
}
