#include "main.h"
#include <libintl.h>
#include <endian.h>
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
	while (1)
	{
		// read in the mio
		struct MiO header;
		if (fread(&header, sizeof(header), 1, fp) != 1)
		{
			if (feof(fp)) break; // just leave on the last section

			int error = errno;
			fprintf(stderr,
				gettext("%s: Failed to read from input file `%s', %s\n"),
				self, path, strerror(error));
			errors++;
			break;
		}

		long size = le64toh(header.size);

		// check for symbols
		// check for gaps

		// allocate data for it
		long oldSize = inp->size;
		inp->size += size+sizeof(struct MiO);
		void *buf = realloc(inp->data, inp->size);
		if (!buf)
		{
			int error = errno;
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(error));
			errors++;
			inp->size -= size-sizeof(struct MiO);
			break;
		}
		inp->data = buf;

		// read in the data
		memcpy(&inp->data[oldSize], (void *)&header, sizeof(header));
		if ((long)fread(&inp->data[oldSize+sizeof(struct MiO)], 1, size, fp)
			!= size)
		{
			if (feof(fp))
			{
				fprintf(stderr,
					gettext("%s: Premature end of file `%s'\n"),
					self, path);
				errors++;
				break;
			}

			int error = errno;
			fprintf(stderr,
				gettext("%s: Failed to read from file `%s', %s\n"),
				self, path, strerror(error));
			errors++;
			break;
		}

		// merge architecture section
		// error on maps section
	}

	fclose(fp);
}
