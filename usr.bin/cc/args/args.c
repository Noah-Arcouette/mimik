#include "../args.h"
#include "../main.h"
#include <libintl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct args_flags args_flags = {
	.preprocess_only = 0,
	.freestanding = 0,
	.outfile = NULL
};

void
args (int argc, char *argv[])
{
	while (1)
	{
		int c = getopt(argc, argv, "+Ef:I:o:");

		switch (c)
		{
		case 'E':
			args_flags.preprocess_only = 1;
			break;
		case 'f':
			if (!strcmp(optarg, "freestanding"))
			{
				args_flags.freestanding = 1;
			}
			else
			{
				fprintf(stderr, gettext("%s: Unknown flag `-f%s'\n"), self,
					optarg);
				errors++;
			}
			break;
		case 'I':
			args_addInclude(optarg, 0);
			break;
		case 'o':
			if (strcmp(optarg, "-") && access(optarg, W_OK) && errno != ENOENT)
			{
				fprintf(stderr, gettext(
					"%s: Failed to get write access to file `%s', %s\n"),
					self, optarg, strerror(errno));
				errors++;
			}
			args_flags.outfile = optarg;
			break;
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

	if (!args_flags.freestanding)
	{
		args_addInclude("/usr/include/", 0);
		args_addInclude("/usr/local/include/", 1);
	}
}
