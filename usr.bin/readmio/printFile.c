#include "main.h"
#include <libintl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void
printFile (const char *file)
{
	// open the file
	FILE *fp;
	if (strcmp(file, "-"))
	{
		fp = fopen(file, "r");
	}
	else
	{
		fp = stdin;
	}

	// failed
	if (!fp)
	{
		int error = errno;
		fprintf(stderr,
			gettext("%s: Failed to open file `%s' for reading, %s\n"),
			self, file, strerror(error));
		errors++;
		return;
	}

	// print the header
	printf(gettext("\n%s:\n"), file);

	// print each section
	while (printSection(fp, file))
	{
		// do nada
	}

	fclose(fp);
}
