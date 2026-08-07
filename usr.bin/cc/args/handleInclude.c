#include "../args.h"
#include "../main.h"
#include <libintl.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

long args_system_includes = ARGS_SYSTEM_INCLUDES;
const struct args_include args_system_include[ARGS_SYSTEM_INCLUDES] = {
	{ .path = "/usr/include/" },
	{ .path = "/usr/local/include/" }
};

struct args_include *args_include  = NULL;
long                 args_includes = 0l;

void
args_handleInclude (const char *path)
{
	if (!strcasecmp(path, "nodefault"))
	{
		args_system_includes = 0; // no system includes
		return;
	}
	// else

	// see if its readable
	if (access(path, R_OK))
	{
		fprintf(stderr, gettext("%s: Include path `%s' not readable, %s\n"),
			self, path, strerror(errno));
		errors++;
		return;
	}

	// allocate memory
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

	// add it to the list
	args_include[args_includes-1].path = path;
}
