#include "../main.h"
#include "../args.h"
#include <libintl.h>
#include <strings.h>
#include <stdio.h>

enum args_machine args_machine = ARGS_MACHINE_NONE;

void
args_handleMachine (const char *opt)
{
	if (!strcasecmp(opt, "i8086"))
	{
	#ifdef SUPPORT_X86_16
		if (args_machine != ARGS_MACHINE_NONE)
		{
			fprintf(stderr,
				gettext("%s: Cannot set machine architecture twice\n"), self);
			errors++;
		}
		args_machine = ARGS_MACHINE_I8086;
	#else
		goto _unsup;
	#endif
	}
	else
	{
		fprintf(stderr, gettext("%s: Unknown machine option `%s'\n"), self,
			opt);
		errors++;
	}
	return;

_unsup:
	fprintf(stderr, gettext("%s: Unsupported machine option `%s'\n"),
		self, opt);
	errors++;
}
