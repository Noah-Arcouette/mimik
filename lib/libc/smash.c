#include <stdint.h>
#include <stdlib.h>

#if UINT16_MAX == UINTPTR_MAX
uintptr_t __stack_chk_guard = 0xe39b;
#elif UINT32_MAX == UINTPTR_MAX
uintptr_t __stack_chk_guard = 0x7e339b28;
#elif UINT64_MAX == UINTPTR_MAX
uintptr_t __stack_chk_guard = 0xa7ee33098b32891a;
#else
#   error "libc/smash.c: Unknown uintptr_t size"
#endif

void
__stack_chk_fail (void)
{
    abort();
}
