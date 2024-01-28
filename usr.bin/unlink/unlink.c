#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <nl_types.h>

#define FAILED "%s: Failed to unlink file `%s', errno %d: %s\n"
#define CATD_FAILED "%s: Failed to open current locale message catalogue, errno %d: %s\n"
#define DEFAULT_SELF "/usr/bin/unlink"

int
main (const int argc, const char **argv)
{
#ifdef RESILIENT
	const char *self = DEFAULT_SELF;
	if (argc > 0)
	{
		self = argv[0];
	}
#else
	const char *self = argv[0];
#endif

	nl_catd catd = catopen("unlink", 0);
	if (catd == (nl_catd)-1)
	{
		fprintf(stderr, CATD_FAILED, self, errno, strerror(errno));
	}

	unsigned int err = 0;
	for (int i = 1; i<argc; i++)
	{
		if (unlink(argv[i]) < 0)
		{
			fprintf(stderr, catgets(catd, 1, 1, FAILED), self, argv[i], errno, strerror(errno));
			err = 1;
		}
	}

	if (catd != (nl_catd)-1)
	{
		catclose(catd);
	}

	return err;
}
