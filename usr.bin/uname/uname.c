#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <errno.h>
#include <nl_types.h>

#define FLAGS_MACHINE 0b00001
#define FLAGS_NODE    0b00010
#define FLAGS_RELEASE 0b00100
#define FLAGS_SYSTEM  0b01000
#define FLAGS_VERSION 0b10000

int 
main (const int argc, const char **argv) 
{
#ifdef RESILIENT
	const char *self = "/usr/bin/uname";

	if (argc > 0)
	{
		self = argv[0];
	}
#else
	const char *self = argv[0];
#endif

	// open catalogue
	nl_catd catd = catopen("uname", 0);
	if (catd == (nl_catd)-1)
	{
		fprintf(stderr, "%s %d: Failed to open catalogue, error %s\n", self, errno, strerror(errno));
	}


	// get flags
	unsigned char flags = 0;
	for (int i = 1; i<argc; i++)
	{
		if (argv[i][0] == '-')
		{
			for (int j = 1; argv[i][j]; j++)
			{
				switch (argv[i][j])
				{
				case 'a':
					flags |= FLAGS_MACHINE | 
							 FLAGS_NODE | 
							 FLAGS_RELEASE | 
							 FLAGS_SYSTEM | 
							 FLAGS_VERSION;
					break;
				case 'm':
					flags |= FLAGS_MACHINE;
					break;
				case 'n':
					flags |= FLAGS_NODE;
					break;
				case 'r':
					flags |= FLAGS_RELEASE;
					break;
				case 's':
					flags |= FLAGS_SYSTEM;
					break;
				case 'v':
					flags |= FLAGS_VERSION;
					break;
				default:
					fprintf(stderr, 
						catgets(catd, 1, 2, "%s: Unknown option `-%c'\n"), 
						self, argv[i][j]);
					break;
				}
			}
		}
	}
	if (!flags)
	{
		flags |= FLAGS_SYSTEM;
	}

	// get uname
	struct utsname name;
	if (uname(&name) < 0)
	{
		fprintf(stderr, 
			catgets(catd, 1, 1, "%s %d: uname failed, error %s\n"), 
			self, errno, strerror(errno));
	}

	// print uname
	if (flags & FLAGS_SYSTEM)
	{
		printf("%s ", name.sysname);
	}
	if (flags & FLAGS_NODE)
	{
		printf("%s ", name.nodename);
	}
	if (flags & FLAGS_RELEASE)
	{
		printf("%s ", name.release);
	}
	if (flags & FLAGS_VERSION)
	{
		printf("%s ", name.version);
	}
	if (flags & FLAGS_MACHINE)
	{
		printf("%s ", name.machine);
	}
	printf("\n");
	
	// close catalogue
	if (catd != (nl_catd)-1)
	{
		catclose(catd);
	}

	return 0;
}
