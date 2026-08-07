#include "../args.h"
#include "../main.h"
#include <libintl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct args_file *args_file  = NULL;
long              args_files = 0l;

void
args_handleFile (const char *name)
{
	// see if the file exists
	if (access(name, R_OK))
	{
		fprintf(stderr, gettext("%s: File `%s' is not readable, %s\n"),
			self, name, strerror(errno));
		errors++;
		return;
	}

	// check the file extension
	enum args_file_type type;
	char *ending = strrchr(name, '.');
	if (!ending)
	{
	_unsup:
		fprintf(stderr, gettext("%s: Unsupported input file type, `%s'\n"),
			self, name);
		errors++;
		return;
	}
	ending++;
	if (!strcmp(ending, "c"))
	{
		type = ARGS_FILE_TYPE_C;
	}
	else if (!strcmp(ending, "s"))
	{
		type = ARGS_FILE_TYPE_S;
	}
	else if (!strcmp(ending, "o"))
	{
		type = ARGS_FILE_TYPE_O;
	}
	else goto _unsup;

	// allocate more room
	args_files++;
	void *buf = realloc(args_file,
		sizeof(struct args_file)*args_files);
	if (!buf)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
	_fail:
		args_files--;
		errors++;
		return;
	}
	args_file = buf;

	// add it to the input list
	struct args_file *f = &args_file[args_files-1];
	f->path = strdup(name);
	if (!f->path)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		goto _fail;
	}

	f->fp = fopen(name, "r");
	if (!f->fp)
	{
		free(f->path);
		fprintf(stderr,
			gettext("%s: Failed to open file `%s' for reading, %s\n"),
			self, name, strerror(errno));
		goto _fail;
	}

	f->type = type;
}
