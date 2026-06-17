#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>

void
printSymbols (FILE *fp, unsigned long long size)
{
	long off = ftell(fp);

	// get the amount of symbols in the section
	long symbols = size/sizeof(struct MiO_Symbol);

	printf("\n");
	if (size % sizeof(struct MiO_Symbol))
	{
		printf(gettext("\tError, size of section is not \
a multiple of the symbol data size\n"));
		errors++;
	}

	// print each symbol out
	while (symbols--)
	{
		struct MiO_Symbol sym;
		if (fread(&sym, sizeof(sym), 1, fp) != 1)
		{
			int error = errno;
			printf(gettext("\tFailed to read from file, %s\n"),
				strerror(error));
			errors++;
			break;
		}

		// print the symbol data
		int flags = le16toh(sym.flags);
		printf(gettext(
			"\n\tOffset : %llu"
			"\n\tSize   : %llu"
			"\n\tFlags  : %04x ("
		),
			(unsigned long long)le64toh(sym.offset),
			(unsigned long long)le64toh(sym.size),
			flags);

		if (flags & MIO_SYMBOL_FLAG_VIRTUAL)
		{
			printf(gettext(" Virtual"));
		}
		if (flags & MIO_SYMBOL_FLAG_READABLE)
		{
			printf(gettext(" Readable"));
		}
		if (flags & MIO_SYMBOL_FLAG_WRITABLE)
		{
			printf(gettext(" Writable"));
		}
		if (flags & MIO_SYMBOL_FLAG_EXECUTABLE)
		{
			printf(gettext(" Executable"));
		}
		if (flags & MIO_SYMBOL_FLAG_GLOBAL)
		{
			printf(gettext(" Global"));
		}
		if (flags & MIO_SYMBOL_FLAG_LITERAL)
		{
			printf(gettext(" Literal"));
		}

		printf(gettext(" )\n\tName   : %.*s\n"),
			(int)sizeof(sym.name), (char *)sym.name);
	}

	// get to the end
	fseek(fp, off+size, SEEK_SET);
}
