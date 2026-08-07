#include "../main.h"
#include "../args.h"
#include <libintl.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

const char *args_outputFile = "a.out";

void
args (int argc, char *argv[])
{
	while (1)
	{
		int c = getopt(argc, argv, "+B:cI:m:o:");

		switch (c)
		{
		case 'c':
			args_handleMode("object");
			break;
		case 'B':
			args_handleMode(optarg);
			break;
		case 'I':
			args_handleInclude(optarg);
			break;
		case 'm':
			args_handleMachine(optarg);
			break;
		case 'o':
			// see if its writable or nonexistant
			if (access(optarg, W_OK) && errno != ENOENT)
			{
				fprintf(stderr,
					gettext("%s: Output file `%s' not writable, %s\n"),
					self, optarg, strerror(errno));
				errors++;
			}
			args_outputFile = optarg;
			break;
		case -1:
			if (optind >= argc || !argv[optind]) return;

			// this is a file
			args_handleFile(argv[optind]);
			optind++;
			return;
		case '?':
		case ':':
			errors++;
			break;
		}
	}

	if (args_machine == ARGS_MACHINE_NONE)
	{
		args_machine = ARGS_MACHINE_DEFAULT;
	}
}
