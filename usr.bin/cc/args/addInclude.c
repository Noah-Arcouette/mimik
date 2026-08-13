#include "../args.h"
#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

struct args_include *args_include  = NULL;
int                  args_includes = 0;

void
args_addInclude (const char *path, int mayfail)
{
	if (access(path, R_OK))
	{
		if (mayfail) return;

		fprintf(stderr, gettext("%s: Failed to access include path `%s', %s\n"),
			self, path, strerror(errno));
		errors++;
		return;
	}

	// allocate room
	args_includes++;
	void *buf = realloc(args_include,
		sizeof(struct args_include)*args_includes);
	if (!buf)
	{
		args_includes--;
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		return;
	}
	args_include = buf;

	// set it up
	args_include[args_includes-1].path = path;
}
