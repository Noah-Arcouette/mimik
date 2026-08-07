#include "../args.h"
#include "../main.h"
#include <libintl.h>
#include <strings.h>
#include <stdio.h>

enum args_mode args_mode = ARGS_MODE_DEFAULT;

void
args_handleMode (const char *mode)
{
	if (!strcasecmp(mode, "object"))
	{
		args_mode = ARGS_MODE_OBJECT;
	}
	else
	{
		fprintf(stderr, gettext("%s: Unknown output mode `%s'\n"), self, mode);
		errors++;
	}
}
