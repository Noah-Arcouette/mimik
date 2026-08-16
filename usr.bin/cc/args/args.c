#include "../args.h"
#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct args_flags args_flags = {
	.preprocess_only = 0,
	.assembler_only = 0,
	.freestanding = 0,
	.outfile = NULL
};

enum args_machine args_machine = ARGS_MACHINE_DEFAULT;

void
args (int argc, char *argv[])
{
	while (1)
	{
		int c = getopt(argc, argv, "+Ef:I:m:o:S");

		switch (c)
		{
		case 'E':
			args_flags.preprocess_only = 1;
			break;
		case 'S':
			args_flags.assembler_only = 1;
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
		case 'm':
			#ifdef SUPPORT_X86_16
			if (!strcmp(optarg, "i8086"))
			{
				args_machine = ARGS_MACHINE_I8086;
			}
			else
			#endif
			{
				fprintf(stderr,
					gettext("%s: Unsupported machine target `%s'\n"), self,
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
			if (optind >= argc || !argv[optind]) goto _leave;

			// check for --
			if (!strcmp(argv[optind-1], "--"))
			{
				// the rest are files
				for (int i = optind; i<argc; i++)
				{
					args_addFile(argv[i]);
				}
				goto _leave;
			}

			args_addFile(argv[optind]);
			optind++;
		}
	}

_leave:
	pre_addMacro("__mimik__", "1");
	if (!args_flags.freestanding)
	{
		args_addInclude("/usr/include/", 0);
		args_addInclude("/usr/local/include/", 1);
	}

	// machine setting
	switch (args_machine)
	{
	case ARGS_MACHINE_NONE:
		fprintf(stderr, gettext("%s: No machine target was set\n"), self);
		errors++;
		break;
	case ARGS_MACHINE_I8086:
		pre_addMacro("__i8086__", "1");
		pre_addMacro("__x86_16__", "1");
		break;
	}
}
