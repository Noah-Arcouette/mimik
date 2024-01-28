#include <stdio.h>
#include <unistd.h>
#include <nl_types.h>
#include <errno.h>
#include <string.h>

#define DEFAULT_SELF "/usr/bin/link"
#define ARG_ERROR "%s: Not enough, or to much, arguments\n"
#define LINK_ERROR "%s: Link failed, errno %d: %s\n"
#define CATD_ERROR "%s: Cannot open current locale message catalogue, errno %d: %s\n"

int
main (const int argc, const char **argv)
{
	int err = 0;

#ifdef RESILIENT
	const char *self = DEFAULT_SELF;
	if (argc > 0)
	{
		self = argv[0];
	}
#else
	const char *self = argv[0];
#endif

	nl_catd catd = catopen("link", 0);
	if (catd == (nl_catd)-1)
	{
		fprintf(stderr, CATD_ERROR, self, errno, strerror(errno));
	}

	if (argc != 3)
	{
		fprintf(stderr, catgets(catd, 1, 1, ARG_ERROR), self);
	}

	if (argc >= 3)
	{
		if (link(argv[1], argv[2]) < 0)
		{
			fprintf(stderr, catgets(catd, 1, 2, LINK_ERROR), self, errno, strerror(errno));
			err = 1;
		}
	}

	if (catd != (nl_catd)-1)
	{
		catclose(catd);
	}

	return err;
}
