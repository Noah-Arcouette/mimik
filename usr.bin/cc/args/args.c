#include "../args.h"
#include "../main.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void
args (int argc, char *argv[])
{
	while (1)
	{
		int c = getopt(argc, argv, "+");

		switch (c)
		{
		case '?':
		case ':':
			errors++;
			break;
		case -1:
			// no more to parse
			if (optind >= argc || !argv[optind]) return;

			// check for --
			if (!strcmp(argv[optind-1], "--"))
			{
				// the rest are files
				for (int i = optind; i<argc; i++)
				{
					args_addFile(argv[i]);
				}
				return;
			}

			args_addFile(argv[optind]);
			optind++;
		}
	}
}
