#include "main.h"
#include "args.h"
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
preprocessOnly (void)
{
	FILE *outfile = stdout;
	if (args_flags.outfile)
	{
		// - : its already stdout
		if (strcmp(args_flags.outfile, "-"))
		{
			outfile = fopen(args_flags.outfile, "w");
			if (!outfile)
			{
				fprintf(stderr, gettext(
					"%s: Failed to open file `%s' for writing, %s\n"),
					self, args_flags.outfile, strerror(errno));
				errors++;
				return;
			}
		}
	}

	for (int i = 0; i<args_files; i++)
	{
		struct args_file *file = &args_file[i];

		if (file->type != ARGS_FILE_TYPE_C)
		{
			fprintf(stderr, gettext(
				"%s: Refusing to preprocess file `%s', not a C source file\n"),
				self, file->path);
			errors++;
			continue;
		}
	}

	fclose(outfile);
}
