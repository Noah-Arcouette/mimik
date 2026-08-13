#include "../args.h"
#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct args_file *args_file  = NULL;
int               args_files = 0;

void
args_addFile (char *path)
{
	struct args_file file;
	file.path = path;

	char *ext = strrchr(path, '.');
	if (!ext)
	{
	_unknown:
		fprintf(stderr, gettext("%s: Unknown file extension `%s'\n"),
			self, path);
		errors++;
		return;
	}

	// the extension
	ext++;
	if (!strcmp(ext, "c"))
	{
		file.type = ARGS_FILE_TYPE_C;
	}
	else if (!strcmp(ext, "i"))
	{
		file.type = ARGS_FILE_TYPE_I;
	}
	else if (!strcmp(ext, "ir"))
	{
		file.type = ARGS_FILE_TYPE_IR;
	}
	else if (!strcmp(ext, "s"))
	{
		file.type = ARGS_FILE_TYPE_S;
	}
	else if (!strcmp(ext, "o"))
	{
		file.type = ARGS_FILE_TYPE_O;
	}
	else if (!strcmp(ext, "so"))
	{
		file.type = ARGS_FILE_TYPE_SO;
	}
	else if (!strcmp(ext, "a"))
	{
		file.type = ARGS_FILE_TYPE_A;
	}
	else goto _unknown;

	// open the file
	file.fp = fopen(path, "r");
	if (!file.fp)
	{
		fprintf(stderr,
			gettext("%s: Failed to open file `%s' for reading, %s\n"),
			self, path, strerror(errno));
		errors++;
		return;
	}

	// add it to the list
	void *buf = realloc(args_file, sizeof(struct args_file)*(args_files+1));
	if (!buf)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		fclose(file.fp);
		return;
	}
	args_file = buf;
	memcpy(&args_file[args_files], &file, sizeof(struct args_file));
	args_files++;
}
