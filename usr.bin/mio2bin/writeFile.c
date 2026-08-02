#include "main.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
writeFile (const char *inpname)
{
	FILE *fp;
	if (outputfile)
	{
		if (!strcmp(outputfile, "w"))
		{
			fp = stdout;
		}
		else
		{
			fp = fopen(outputfile, "w");
			if (!fp)
			{
				fprintf(stderr,
					gettext("%s: Failed to open file `%s' for writing, %s\n"),
					self, outputfile, strerror(errno));
				errors++;
				return;
			}
		}
	}
	else
	{
		outputfile = malloc(strlen(inpname)+4 /* .bin */ +1 /* \0 */);
		if (!outputfile)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			return;
		}

		// build the path
		strcpy(outputfile, inpname);
		strcat(outputfile, ".bin");

		// try to open the file
		fp = fopen(outputfile, "w");
		if (!fp)
		{
			fprintf(stderr,
				gettext("%s: Failed to open file `%s' for writing, %s\n"),
				self, outputfile, strerror(errno));
			errors++;
			free(outputfile);
			return;
		}
	}

	// write the file
	if (fwrite(outbuf, 1, outbufsz, fp) != (size_t)outbufsz)
	{
		fprintf(stderr, gettext("%s: Failed to write to output file, %s\n"),
			self, strerror(errno));
		errors++;
	}

	fclose(fp);
}
