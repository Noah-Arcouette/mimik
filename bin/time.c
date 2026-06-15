#include <sys/times.h>
#include <sys/wait.h>
#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("time");

	// check arguments
	int c;
	do
	{
		c = getopt(argc, argv, "p");
		switch (c)
		{
		case 'p': // ignored
			break;
		case ':':
		case '?':
			return 1;
		}
	} while (c != -1);

	// fork
	pid_t chld = fork();
	if (chld == 0)
	{
		// exec
		if (execvp(argv[optind], &argv[optind]) == -1)
		{
			int error = errno;
			fprintf(stderr,
				gettext("%s: execv failed, %s\n"), argv[0], strerror(error));
			if (ENOENT) return 127;
			return 126;
		}

		return 1;
	}
	else if (chld == -1)
	{
		int error = errno;
		fprintf(stderr,
			gettext("%s: fork failed, %s\n"), argv[0], strerror(error));
		return 1;
	}

	// start timer
	clock_t startClock;
	if ((startClock = times(NULL)) == -1)
	{
		int error = errno;
		fprintf(stderr,
			gettext("%s: times failed, %s\n"), argv[0], strerror(error));
		return 1;
	}

	// wait
	int status = 0;
	if (wait(&status) == -1)
	{
		int error = errno;
		fprintf(stderr,
			gettext("%s: wait failed, %s\n"), argv[0], strerror(error));
		return 1;
	}

	// stop timer
	struct tms timer;
	clock_t stopClock;
	if ((stopClock = times(&timer)) == -1)
	{
		int error = errno;
		fprintf(stderr,
			gettext("%s: times failed, %s\n"), argv[0], strerror(error));
		return 1;
	}

	// the times
	float clocksPerSec = sysconf(_SC_CLK_TCK);
	float realTime = ((float)stopClock-(float)startClock)/clocksPerSec;
	float userTime = (float)timer.tms_cutime/clocksPerSec;
	float sysTime  = (float)timer.tms_cstime/clocksPerSec;

	// report time
	fprintf(stderr, "real %f\nuser %f\nsys %f\n",
		realTime,
		userTime,
		sysTime);

	return 0;
}
