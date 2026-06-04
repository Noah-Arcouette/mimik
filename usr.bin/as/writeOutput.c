#include "main.h"
#include "emit.h"
#include <libintl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void
writeOutput (void)
{
	// open the output file
	FILE *outputfp = fopen(arguments.outputfile, "w");
	if (!outputfp)
	{
		int error = errno;
		fprintf(stderr,
			gettext("%s: Failed to open output file for writing, %s\n"),
			self, strerror(error));
		errors++;
		return;
	}

	if (emitbuf && emitsz > 0)
	{
		// write to the file
		if ((long)fwrite(emitbuf, 1, emitsz, outputfp) != emitsz)
		{
			int error = errno;
			fprintf(stderr, gettext("%s: Failed to write to output file, %s\n"),
				self, strerror(error));
			errors++;
		}
	}

	// close
	fclose(outputfp);
}
