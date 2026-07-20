#include "_zio.h"
#include <pthread.h>

int
ztrylockfile (zFILE *fp)
{
	if (!fp) return 1;

	if (fp->lock) return 1; // is locked
	// lock for access
	fp->lock = 1;

	// check ownership and all
	pthread_t self = pthread_self();
	if (fp->locks > 0) // has locks
	{
		if (fp->locker == self) // our locks
		{
			fp->locks++;
			fp->lock = 0; // open access lock
			return 0; // acquired
		}
		// not our lock
		fp->lock = 0;
		return 1; // not acquired
	}
	// doesn't have a lock
	fp->locker = self;
	fp->locks  = 1;
	fp->lock   = 0;
	return 0; // acquired
}
