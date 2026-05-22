#include <libintl.h>
#include <unistd.h>
#include <stdio.h>

int
main (void)
{
	// not a tty
	if (!isatty(STDIN_FILENO))
	{
		puts(gettext("not a tty"));
		return 1;
	}

	char *name = ttyname(STDIN_FILENO);
	// error
	if (!name)
	{
		perror("ttyname");
		return 2;
	}

	puts(name);
	return 0;
}
