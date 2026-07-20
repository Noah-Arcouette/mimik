#include "_zio.h"
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

zFILE *
zopen (const char *restrict path, const char *restrict mode, int format)
{
	if (!path | !mode)
	{
		errno = EINVAL;
		return NULL;
	}

	// the option letters
	#define OPTS_PLUS 1
	#define OPTS_E    2
	#define OPTS_X    4
	#define OPTS_S    8
	int opts = 0;
	const char *s = mode+1;
	while (*s)
	{
		switch (*s)
		{
		case '\0':
		case 'b':
			break;
		case '+':
			opts |= OPTS_PLUS;
			break;
		case 'e':
			opts |= OPTS_E;
			break;
		case 'x':
			opts |= OPTS_X;
			break;
		case 's':
			opts |= OPTS_S;
			break;
		default:
			errno = EINVAL;
			return NULL;
		}
		s++;
	}

	// the mode
	int oflags;
	switch (mode[0])
	{
	case 'r':
		if (opts & OPTS_PLUS)
		{
			oflags = O_RDWR;
		}
		else
		{
			oflags = O_RDONLY;
		}
		break;
	case 'w':
		if (opts & OPTS_PLUS)
		{
			oflags = O_RDWR|O_CREAT|O_TRUNC;
		}
		else
		{
			oflags = O_WRONLY|O_CREAT|O_TRUNC;
		}
		break;
	case 'a':
		if (opts & OPTS_PLUS)
		{
			oflags = O_RDWR|O_CREAT|O_APPEND;
		}
		else
		{
			oflags = O_WRONLY|O_CREAT|O_APPEND;
		}
		break;
	default:
		errno = EINVAL;
		return NULL;
	}

	if (opts & OPTS_E) oflags |= O_CLOEXEC;
	if (opts & OPTS_X) oflags |= O_EXCL;

	// open
	int fd = open(path, oflags, 0666);
	if (fd == -1) return NULL;

	// zdopen
	zFILE *fp = zdopen(fd, mode, format);
	if (!fp) // error
	{
		int e = errno;
		close(fd);
		errno = e;
		return NULL;
	}
	// else, good
	return fp;
}
