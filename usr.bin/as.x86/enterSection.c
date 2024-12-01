#include <stdio.h>
#include "defs.h"
#include <mio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void
enterSection (const char *restrict section, const char *restrict flags)
{
	printf("Parser: Enter section `%s', flags `%s'\n", section, flags);

	// find existing section or new section to make
	currentSection = firstSection; // start at the top
	while (currentSection)
	{
		// section exists
		if (!strcmp(section, currentSection->name))
		{
			// redefined flags
			if (*flags)
			{
				fprintf(stderr, "%s:%d: Redefined flags on already defined section, ignoring flags.\n", filename, lineno-1);
			}

			// leave
			return;
		}

		currentSection = currentSection->next;
	}

	// section doesn't exist
	currentSection = (struct section *)malloc(sizeof(struct section));

	// check if allocation worked
	int errnum;
	if (!currentSection)
	{
	memerror:
		errnum = errno;
		fprintf(stderr, "%s: Failed to allocate memory.\n", self);
		fprintf(stderr, "Errno %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}

	// initialize section
	currentSection->size   = 0;
	currentSection->buffer = (char *)NULL;
	currentSection->stream      = open_memstream(
		&currentSection->buffer,
		&currentSection->size
	);
	if (!currentSection->stream)
	{
		currentSection->buffer = (char *)NULL;
		goto memerror;
	}
	currentSection->firstSymbol = (struct symbol *)NULL;
	currentSection->firstGap    = (struct gap    *)NULL;
	currentSection->bssz        = 0;
	currentSection->flags       = 0;

	// assign name
	currentSection->name = strdup(section);
	// check if it worked
	if (!currentSection->name)
	{
		goto memerror;
	}

	// add flags
	while (*flags)
	{
		switch (*flags)
		{
		case 'r':
			currentSection->flags |= MIO_SECTION_FLAG_PERMISSION_READ;
			break;
		case 'w':
			currentSection->flags |= MIO_SECTION_FLAG_PERMISSION_WRITE;
			break;
		case 'x':
			currentSection->flags |= MIO_SECTION_FLAG_PERMISSION_EXECUTE;
			break;
		case 'b':
			currentSection->flags |= MIO_SECTION_FLAG_BSS;
			break;
		case 'a': // ignore for compatibility, for now
			break;
		default:
			fprintf(stderr, "%s:%d: Unknown section flag `%c'.\n", filename, lineno-1, *flags);
			break;
		}

		flags++;
	}

	// add into list
	if (firstSection)
	{
		struct section *tail = firstSection->next;
		firstSection  ->next = currentSection;
		currentSection->next = tail;
		return;
	}

	currentSection->next = (struct section *)NULL;
	firstSection         = currentSection;
}
