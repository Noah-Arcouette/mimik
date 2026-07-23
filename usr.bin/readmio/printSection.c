#include "main.h"
#include <inttypes.h>
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <errno.h>
#include <stdio.h>
#include <mio.h>

int
printSection (FILE *fp, const char *path)
{
	struct MiO section;
	if (fread(&section, sizeof(section), 1, fp) != 1)
	{
		int error = errno;

		if (feof(fp)) return 0; // EOF

		// error
		fprintf(stderr, gettext("%s: Failed to read from file `%s', %s\n"),
			self, path, strerror(error));
		errors++;
		return 0;
	}

	// print the section information
	printf(gettext("%.*s:\n"),
		(int)sizeof(section.name),
		(char *)section.name);

	// size
	unsigned long long size = le64toh(section.size);
	printf(gettext("\tSize:  %llu\n"), size);

	// magic
	int magicGood = (le32toh(section.magic) == MIO_MAGIC);
	printf(gettext("\tMagic: %08x ("), le32toh(section.magic));
	if (magicGood)
	{
		printf(gettext("Good)\n"));
	}
	else
	{
		printf(gettext("Bad)\n"));
	}

	// flags
	printf(gettext("\tFlags: %02x ("), section.flags);
	if (section.flags & MIO_FLAG_VIRTUAL)
	{
		printf(gettext(" Virtual"));
	}
	printf(gettext(" )\n"));

	// check for corruption
	if (!magicGood)
	{
		errors++;
		return 0;
	}

	// check the name of the section
	if (!strncmp( // mio.arch
		(char *)section.name,
		(char *)MIO_SPECIAL_MIO_ARCH,
		sizeof(section.name)))
	{
		if (section.flags & MIO_FLAG_VIRTUAL)
		{
			printf(gettext("\n\tError, refusing to read from virtual data\n"));
			errors++;
		}
		else
		{
			printArch(fp, size);
		}
	}
	else if (!strncmp( // mio.symbols
		(char *)section.name,
		(char *)MIO_SPECIAL_MIO_SYMBOLS,
		sizeof(section.name)))
	{
		if (section.flags & MIO_FLAG_VIRTUAL)
		{
			printf(gettext("\n\tError, refusing to read from virtual data\n"));
			errors++;
		}
		else
		{
			printSymbols(fp, size);
		}
	}
	else if (!strncmp( // mio.gaps
		(char *)section.name,
		(char *)MIO_SPECIAL_MIO_GAPS,
		sizeof(section.name)))
	{
		if (section.flags & MIO_FLAG_VIRTUAL)
		{
			printf(gettext("\n\tError, refusing to read from virtual data\n"));
			errors++;
		}
		else
		{
			printGaps(fp, size);
		}
	}
	else if (!strncmp( // mio.maps
		(char *)section.name,
		(char *)MIO_SPECIAL_MIO_MAPS,
		sizeof(section.name)))
	{
		if (section.flags & MIO_FLAG_VIRTUAL)
		{
			printf(gettext("\n\tError, refusing to read from virtual data\n"));
			errors++;
		}
		else
		{
			printMaps(fp, size);
		}
	}
	else if (!strncmp( // mio.entry
		(char *)section.name,
		(char *)MIO_SPECIAL_MIO_ENTRY,
		sizeof(section.name)))
	{
		if (section.flags & MIO_FLAG_VIRTUAL)
		{
			printf(gettext("\n\tError, refusing to read from virtual data\n"));
			errors++;
		}
		else
		{
			printEntry(fp, size);
		}
	}
	else // just skip the data
	{
		fseek(fp, size, SEEK_CUR);
	}
	return 1;
}
