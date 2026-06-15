#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#include "emit.h"
#include "main.h"

const char *self;
int errors = 0;

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("as");

	self = argv[0];

	// parse arguments
	args(argc, argv);
	if (errors) return 1;

	// lexer testing
	for (int i = optind; i<argc; i++)
	{
		// open the file
		lfilename = argv[i];
		if (!strcmp(lfilename, "-"))
		{
			lfp = stdin;
		}
		else
		{
			lfp = fopen(lfilename, "r");
			if (!lfp)
			{
				int error = errno;
				fprintf(stderr, gettext("%s: %s: %s\n"),
					self, lfilename, strerror(error));
				errors++;
				continue; // skip if there's an error
			}
		}

		// parse the new file
		parse();

		// free the file
		fclose(lfp);

		resetToken();
	}
	destroyToken();

	// create architecture section
	emitArchitecture();

	// create symbol section

	// create gap section
	emitGapData();

	// emit the mio file
	if (!errors) writeOutput();
	freeEmit();

	if (errors) return 1;
	return 0;
}
