#include "main.h"
#include "args.h"
#include "pre.h"
#include <libintl.h>
#include <locale.h>

const char *self;

int errors = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("cc");

	// parse the command line arguments
	args(argc, argv);

	// pre-process only
	if (args_flags.preprocess_only)
	{
		if (!errors) preprocessOnly();
		args_freeFiles();
		args_freeIncludes();
		srch_free(&pre_macro);
		if (errors) return 1;
		return 0;
	}
	// else

	// .c, .i => .s
	for (int i = 0; i<args_files; i++)
	{
		struct args_file *file = &args_file[i];

		if (file->type != ARGS_FILE_TYPE_C &&
			file->type != ARGS_FILE_TYPE_I) continue;

		compileCFile(file);
	}
	lex_free();
	args_freeIncludes();
	srch_free(&pre_macro);
	// .s => .o
	// .o, .a, .so => .so, exec

	args_freeFiles();

	if (errors) return 1;
	return 0;
}
