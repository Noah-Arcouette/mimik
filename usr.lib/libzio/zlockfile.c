#include "_zio.h"
#include <sched.h>

void
zlockfile (zFILE *fp)
{
	if (!fp) return;

	while (ztrylockfile(fp))
	{
		sched_yield();
	}
}
