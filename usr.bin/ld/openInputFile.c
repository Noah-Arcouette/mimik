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

	long symbolsOffset = -1;
	long gapsOffset    = -1;
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

		// allocate data for it
		if (header.flags & MIO_FLAG_VIRTUAL)
		{
			size = 0; // no physical size
		}

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

		void *startOfSection = &inp->data[oldSize+sizeof(struct MiO)];
		if (size) // only if data needs to be read in
		{
			if ((long)fread(startOfSection, 1, size, fp) != size)
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
		}

		// check for symbols
		if (!strncmp(
			(void *)header.name,
			(void *)MIO_SPECIAL_MIO_SYMBOLS,
			sizeof(header.name)))
		{
			if (symbolsOffset >= 0) // already found one
			{
				fprintf(stderr,
					gettext("%s: `%s' has more than one symbol section\n"),
					self, path);
				errors++;
			}
			if (header.flags & MIO_FLAG_VIRTUAL) // is a virtual
			{
				fprintf(stderr,
					gettext(
						"%s: Refusing to use virtual symbol section, `%s'\n"),
					self, path);
				errors++;
			}

			// save the offset and size
			symbolsOffset = inp->size-size;
			inp->symbols  = size/sizeof(struct MiO_Symbol);
		}
		// check for gaps
		else if (!strncmp(
			(void *)header.name,
			(void *)MIO_SPECIAL_MIO_GAPS,
			sizeof(header.name)))
		{
			if (gapsOffset >= 0) // already found one
			{
				fprintf(stderr,
					gettext("%s: `%s' has more than one gap section\n"),
					self, path);
				errors++;
			}
			if (header.flags & MIO_FLAG_VIRTUAL) // may not be a virtual
			{
				fprintf(stderr,
					gettext("%s: Refusing to use virtual gap section, `%s'\n"),
					self, path);
				errors++;
			}

			// save the offset and size
			gapsOffset = inp->size-size;
			inp->gaps  = size/sizeof(struct MiO_Gap);
		}
		// merge architecture section
		else if (!strncmp(
			(void *)header.name,
			(void *)MIO_SPECIAL_MIO_ARCH,
			sizeof(header.name)))
		{
			if (header.flags & MIO_FLAG_VIRTUAL) // may not be a virtual
			{
				fprintf(stderr, gettext(
					"%s: Refusing to use virtual architecture section, `%s'\n"),
					self, path);
				errors++;
			}
			// check the size
			else if (size != sizeof(struct MiO_Arch))
			{
				fprintf(stderr, gettext(
					"%s: Improper size of architecture section in file `%s'\n"),
					self, path);
				errors++;
			}
			// merge the architecture
			else
			{
				struct MiO_Arch *arch = (struct MiO_Arch *)startOfSection;
				mergeArchitecture(path, arch);
			}
		}
		// error on maps section
		else if (!strncmp(
			(void *)header.name,
			(void *)MIO_SPECIAL_MIO_MAPS,
			sizeof(header.name)))
		{
			fprintf(stderr,
				gettext("%s: Refusing to linked loadable object, `%s'"),
				self, path);
			errors++;
		}
		// check for other non-handled special sections
		else if (header.name[0] != '.')
		{
			fprintf(stderr,
				gettext("%s: Unhandled special section `%.*s' in file `%s'\n"),
				self, (int)sizeof(header.name), header.name, path);
			errors++;
		}
	}

	// add the offsets
	if (symbolsOffset > 0)
	{
		inp->symbol = &inp->data[symbolsOffset];
	}
	if (gapsOffset > 0)
	{
		inp->gap = &inp->data[gapsOffset];
	}

	fclose(fp);
}
