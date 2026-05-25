#include <sys/utsname.h>
#include <locale.h>
#include <unistd.h>
#include <stdio.h>

#define MACHINE 0b00001
#define NODE    0b00010
#define RELEASE 0b00100
#define SYSTEM  0b01000
#define VERSION 0b10000

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	int c;
	int errors = 0;

	int settings = 0;

	do
	{
		c = getopt(argc, argv, "amnrsv");

		switch (c)
		{
		case 'a':
			settings = MACHINE|NODE|RELEASE|SYSTEM|VERSION;
			break;
		case 'm':
			settings |= MACHINE;
			break;
		case 'n':
			settings |= NODE;
			break;
		case 'r':
			settings |= RELEASE;
			break;
		case 's':
			settings |= SYSTEM;
			break;
		case 'v':
			settings |= VERSION;
			break;
		case '?':
		case ':':
			errors = 1;
			break;
		}
	} while (c != -1);

	if (!settings) settings |= SYSTEM;

	// print the actual information
	struct utsname name;
	if (uname(&name) < 0)
	{
		perror("uname");
		return 1;
	}

	if (settings & SYSTEM)
	{
		printf("%s ", name.sysname);
	}
	if (settings & NODE)
	{
		printf("%s ", name.nodename);
	}
	if (settings & RELEASE)
	{
		printf("%s ", name.release);
	}
	if (settings & VERSION)
	{
		printf("%s ", name.version);
	}
	if (settings & MACHINE)
	{
		printf("%s ", name.machine);
	}
	printf("\n");

	return errors;
}
