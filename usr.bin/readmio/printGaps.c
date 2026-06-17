#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>

void
printGaps (FILE *fp, unsigned long long size)
{
	long off = ftell(fp);

	// get the amount of gaps in the section
	long gaps = size/sizeof(struct MiO_Gap);

	printf("\n");
	if (size % sizeof(struct MiO_Gap))
	{
		printf(gettext("\tError, size of section is not \
a multiple of the gap data size\n"));
		errors++;
	}

	// print each symbol out
	while (gaps--)
	{
		struct MiO_Gap gap;
		if (fread(&gap, sizeof(gap), 1, fp) != 1)
		{
			int error = errno;
			printf(gettext("\tFailed to read from file, %s\n"),
				strerror(error));
			errors++;
			break;
		}

		// print the gap data
		int type = le16toh(gap.type);
		printf(gettext(
			"\n\tOffset : %llu"
			"\n\tType   : %04x ("
		), (unsigned long long)le64toh(gap.offset), type);

		switch (type & MIO_GAP_TYPE_MASK)
		{
		case MIO_GAP_TYPE_LIT_BYTE:
			printf(gettext(" Literal Byte"));
			break;
		case MIO_GAP_TYPE_LIT_LE16:
			printf(gettext(" Literal LE16"));
			break;
		case MIO_GAP_TYPE_LIT_LE32:
			printf(gettext(" Literal LE32"));
			break;
		case MIO_GAP_TYPE_LIT_LE64:
			printf(gettext(" Literal LE64"));
			break;
		case MIO_GAP_TYPE_LIT_LE128:
			printf(gettext(" Literal LE128"));
			break;
		case MIO_GAP_TYPE_LIT_BE16:
			printf(gettext(" Literal BE16"));
			break;
		case MIO_GAP_TYPE_LIT_BE32:
			printf(gettext(" Literal BE32"));
			break;
		case MIO_GAP_TYPE_LIT_BE64:
			printf(gettext(" Literal BE64"));
			break;
		case MIO_GAP_TYPE_LIT_BE128:
			printf(gettext(" Literal BE128"));
			break;
		case MIO_GAP_TYPE_DISP_BYTE:
			printf(gettext(" Displacement Byte"));
			break;
		case MIO_GAP_TYPE_DISP_LE16:
			printf(gettext(" Displacement LE16"));
			break;
		case MIO_GAP_TYPE_DISP_LE32:
			printf(gettext(" Displacement LE32"));
			break;
		case MIO_GAP_TYPE_DISP_LE64:
			printf(gettext(" Displacement LE64"));
			break;
		case MIO_GAP_TYPE_DISP_LE128:
			printf(gettext(" Displacement LE128"));
			break;
		case MIO_GAP_TYPE_DISP_BE16:
			printf(gettext(" Displacement BE16"));
			break;
		case MIO_GAP_TYPE_DISP_BE32:
			printf(gettext(" Displacement BE32"));
			break;
		case MIO_GAP_TYPE_DISP_BE64:
			printf(gettext(" Displacement 64"));
			break;
		case MIO_GAP_TYPE_DISP_BE128:
			printf(gettext(" Displacement 128"));
			break;
		default:
			printf(gettext(" Unknown Type"));
			break;
		}

		if (type & MIO_GAP_TYPE_READING)
		{
			printf(gettext(" Reading"));
		}
		if (type & MIO_GAP_TYPE_WRITING)
		{
			printf(gettext(" Writing"));
		}
		if (type & MIO_GAP_TYPE_EXECUTING)
		{
			printf(gettext(" Executing"));
		}

		printf(gettext(" )\n\tSymbol : %.*s\n"),
			(int)sizeof(gap.symbol), (char *)gap.symbol);
	}

	// get to the end
	fseek(fp, off+size, SEEK_SET);
}
