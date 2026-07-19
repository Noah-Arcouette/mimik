#include "_zio.h"
#include <pthread.h>
#include <sched.h>

void
zunlockfile (zFILE *fp)
{
	if (!fp) return;

	// get access lock
	while (fp->lock)
	{
		sched_yield();
	}
	fp->lock = 1; // ours now

	pthread_t self = pthread_self();
	if (fp->locks > 0) // has locks
	{
		if (fp->locker == self) // our lock
		{
			fp->locks--;
			fp->lock = 0;
			return; // all good
		}
		// not our lock
	}
	// no locks
	fp->lock = 0;
	return; // nothing we can do
}
