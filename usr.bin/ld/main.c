#include "main.h"
#include <libintl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

long errors = 0;

const char *self;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("ld");
	srand(time(NULL));

	args(argc, argv);
	if (errors) return 1;

	// open input files
	for (int i = optind; i<argc; i++)
	{
		openInputFile(argv[i]);
	}
	// static symbol renaming
	renameStaticSymbols();

	// global symbol double definition checking
	checkGlobalSymbols();

	// LTO: merge like symbols
	// LTO: remove non-referenced static symbols

	// run the linker script
	linker();

	// check for unused symbols and section

	// raw input data isn't needed anymore
	closeInputFiles();

	// emit entry section
	emitEntrySection();

	// emit architecture section
	emitArchSection();

	// emit gaps section
	// emit symbols section
	// emit maps section

	// emit the output
	if (!errors)
	{
		FILE *fp = fopen(outputFile, "w");
		if (!fp)
		{
			fprintf(stderr,
				gettext("%s: Failed to open file for writing `%s', %s\n"),
				self, outputFile, strerror(errno));
			errors++;
		}
		else
		{
			// write the data
			if (fwrite(outputBuf, 1, outputsz, fp) != (size_t)outputsz)
			{
				fprintf(stderr,
					gettext("%s: Failed to write to output file, %s\n"),
					self, strerror(errno));
				errors++;
			}

			fclose(fp);
		}
	}

	// free the output stuff
	free(outputBuf);

	if (errors) return 1;
	return 0;
}
