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
	int magicGood = (
		section.magic[0] == MIO_MAGIC[0] &&
		section.magic[1] == MIO_MAGIC[1] &&
		section.magic[2] == MIO_MAGIC[2] &&
		section.magic[3] == MIO_MAGIC[3]
	);
	printf(gettext("\tMagic: %02x%02x%02x%02x ("),
		section.magic[0],
		section.magic[1],
		section.magic[2],
		section.magic[3]);
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
	// mio.gaps
	else // just skip the data
	{
		fseek(fp, size, SEEK_CUR);
	}
	return 1;
}
