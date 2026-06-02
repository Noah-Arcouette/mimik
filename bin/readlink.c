#include <libintl.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <stdio.h>
#include <errno.h>

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("readlink");

	// parse arguments
	int newline = 1;
	int c;
	do
	{
		c = getopt(argc, argv, "n");

		switch (c)
		{
		case 'n':
			newline = 0;
			break;
		case '?':
		case ':':
			return 1;
		}
	} while (c != -1);

	// make sure there's the right amount of arguments
	if (argc-optind != 1)
	{
		fprintf(stderr, gettext("%s: Improper amount of operands\n"), argv[0]);
		return 1;
	}

	// get the link
	char buf[BUFSIZ];
	ssize_t sz = readlink(argv[optind], buf, BUFSIZ);
	if (sz == -1)
	{
		int error = errno;
		fprintf(stderr, gettext("%s: %s\n"),
			argv[0],
			strerror(error));
		return 1;
	}
	buf[sz] = '\0';

	if (newline)
	{
		printf("%s\n", buf);
	}
	else
	{
		printf("%s", buf);
	}
}
