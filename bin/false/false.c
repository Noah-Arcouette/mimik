#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <nl_types.h>
#include <errno.h>
#include <string.h>

int 
checkInt (const char *s)
{
	for (int i = 0; s[i]; i++)
	{
		if (!isdigit(s[i]))
		{
			return 0;
		}
	}
	return 1;
}

int 
main (int argc, const char **argv)
{
#ifdef RESILIENT
	const char *self = "/bin/false";

	if (argc > 0)
	{
		self = argv[0];
	}
#else
	const char *self = argv[0];
#endif

	nl_catd catd = catopen("false", 0);
	if (catd == (nl_catd)-1)
	{
		fprintf(stderr, "%s %d: failed to open catalogue, error %s", self, errno, strerror(errno));
	}

	for (int i = 1; i<argc; i++)
	{
		if (checkInt(argv[i]))
		{
			catclose(catd);
			return atoi(argv[i]);
		}
		fprintf(stderr, catgets(catd, 1, 1, "%s: argument `%s' is not a positive integer\n"), self, argv[i]);
	}

	catclose(catd);
	return 1;
}
