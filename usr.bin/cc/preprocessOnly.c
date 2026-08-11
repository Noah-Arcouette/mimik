#include "main.h"
#include "args.h"
#include <libintl.h>
#include <stdio.h>

void
preprocessOnly (void)
{
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
}
