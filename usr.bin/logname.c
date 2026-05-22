#include <unistd.h>
#include <locale.h>
#include <stdio.h>

int
main (void)
{
	setlocale(LC_ALL, "");

	char *name = getlogin();
	if (!name)
	{
		perror("getlogin");
		return 1;
	}
	puts(name);
	return 0;
}
