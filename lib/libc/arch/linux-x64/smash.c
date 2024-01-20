#include <stdint.h>
#include <stdlib.h>

uintptr_t __stack_chk_guard = 0xa7ee33098b32891a;

void
__stack_chk_fail (void)
{
    abort();
}
