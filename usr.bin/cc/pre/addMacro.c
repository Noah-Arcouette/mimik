#include "../main.h"
#include "../srch.h"
#include "../pre.h"
#include <libintl.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

struct srch pre_macro = SRCH_NULL;

void
pre_addMacro (const char *name, const char *value)
{
	// dup the data
	char *dat = strdup(value);
	if (!dat)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		return;
	}

	srch_add(&pre_macro, name, dat);
}
