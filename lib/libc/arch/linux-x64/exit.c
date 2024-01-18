#include <unistd.h>
#define LINUX_X64_ONLY
#   include "syscall.h"
#undef LINUX_X64_ONLY

void
_exit (int status)
{
    __syscall1(SYS_EXIT, (long)(status&0xff));
}
