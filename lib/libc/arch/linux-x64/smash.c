#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

uintptr_t __stack_chk_guard = 0xa7ee33098b32891a;

void
__stack_chk_fail (void)
{
	fputs("Stack smash detected, force exiting...\n", stderr);

	_exit(EFAULT);
}
