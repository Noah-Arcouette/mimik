#include "main.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct inputFile *input  = NULL;
long              inputs = 0;

void
openInputFile (const char *path)
{
	// open the file
	FILE *fp = stdin;
	if (strcmp(path, "-"))
	{
		fp = fopen(path, "r");
		if (!fp)
		{
			int error = errno;
			fprintf(stderr, gettext("%s: Failed to open file `%s', %s\n"),
				self, path, strerror(error));
			errors++;
			return;
		}
	}

	// allocate a new input file
	inputs++;
	void *buf = realloc(input, sizeof(struct inputFile)*inputs);
	if (!buf)
	{
		int error = errno;
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(error));
		inputs--;
		fclose(fp);
		return;
	}
	input = buf;
	struct inputFile *inp = &input[inputs-1]; // the current input file

	// setup input file
	inp->path    = path;
	inp->gap     = NULL;
	inp->gaps    = 0;
	inp->symbol  = NULL;
	inp->symbols = 0;
	inp->data    = NULL;
	inp->size    = 0;

	// read in the file

	// load sections
	// find symbols section
	// find gaps section
	// merge architecture section
	// error on maps section

	fclose(fp);
}
