#include <unistd.h>
#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY

void
_exit (int status)
{
    (void)__syscall1(SYS_EXIT, status&0xff);
}
