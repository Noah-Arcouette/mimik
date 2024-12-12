#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>
#include "../defs.h"

struct inputfile *inputfile   = (struct inputfile *)NULL;
size_t            inputfiles  = 0;
size_t            inputfilecp = 0;

void
ld_input (const char *file)
{
	FILE *fp = fopen(file, "r");
	if (!fp)
	{
		error(errno, "Failed to open file `%s' for reading\n", file);
		return;
	}

	// read the header
	struct MiO_Header h;
	if (fread(&h, sizeof(struct MiO_Header), 1, fp) != 1)
	{
		error(errno, "%s: Failed to read header\n", file);
		goto close_and_leave;
	}

	// validate the header
	if (memcmp(h.magic, MIO_MAGIC, sizeof(h.magic)))
	{
		error(0, "%s: Corrupt magic number\n", file);
		goto close_and_leave;
	}
	if (h.version != MIO_CURRENT_VERSION)
	{
		error(0, "%s: Unsupported format version\n", file);
		goto close_and_leave;
	}
	if (!(h.flags & MIO_HEADER_FLAG_LAST))
	{
		error(0, "%s: FAT Binaries are not supported\n", file);
		goto close_and_leave;
	}

	// allocate new file
	struct inputfile *currfile;
	inputfiles++;
	if (inputfiles > inputfilecp)
	{
		inputfilecp = (3*inputfiles)/2;
		currfile = (struct inputfile *)realloc(inputfile, inputfilecp*sizeof(struct inputfile)); // using currfile as a temp
		if (!currfile)
		{
			inputfilecp = --inputfiles;
			error(errno, "Failed to allocate new file\n");
			goto close_and_leave;
		}
		inputfile = currfile;
	}
	currfile = &inputfile[inputfiles-1];
	memset(currfile, 0, sizeof(struct inputfile)); // nullify

	// set file name
	if (!(currfile->filename = strdup(file)))
	{
		error(errno, "Failed to allocate file name\n");
		goto kill_file_and_leave;
	}

	// upon loading please keep track of file name and add a symbol between sections
	struct MiO_Section *s;
size_t sections  = 0; // use a vector locally, then shrink it to fit later
	size_t sectioncp = 0;
	do
	{
		// allocate new section
		sections++;
		if (sections > sectioncp)
		{
			sectioncp = (3*sections)/2;
			s = (struct MiO_Section *)realloc(inputfile->section, sectioncp*sizeof(struct MiO_Section));
			if (!s)
			{
				error(errno, "Failed to allocate new sections for file");
				goto kill_file_and_leave;
			}
			inputfile->section = s;
		}
		s = &inputfile->section[sections-1];

		// read new section
		if (fread(s, sizeof(struct MiO_Section), 1, fp) != 1)
		{
			error(errno, "%s: Failed to read section from file\n", file);
			goto kill_file_and_leave;
		}

		// make sure the file isn't already linked
		if (!strncmp((const char *)s->name, MIO_MAP_NAME, sizeof(s->name)) ||
		    !strncmp((const char *)s->name, MIO_SEG_NAME, sizeof(s->name)))
		{
			error(0, "%s: File already linked\n", file); // error on these
			goto kill_file_and_leave;
		}
	} while (!(s->flags & MIO_SECTION_FLAG_LAST));

close_and_leave:
	fclose(fp);
	return;
kill_file_and_leave:
	inputfiles--;
	freeFile(currfile);
	fclose(fp);
}
