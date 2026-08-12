#include "main.h"
#include "args.h"
#include "lex.h"
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

	struct lex_context lc = {
		.type = LEX_CONTEXT_TYPE_NORMAL_FILE,
		.lineno = 1,
		.offset = 0,
		.size = 0
	};
	for (int i = 0; i<args_files; i++)
	{
		struct args_file *file = &args_file[i];

		// make sure its a C file
		if (file->type != ARGS_FILE_TYPE_C)
		{
			fprintf(stderr, gettext(
				"%s: Refusing to preprocess file `%s', not a C source file\n"),
				self, file->path);
			errors++;
			continue;
		}

		// push it to the lexer context
		lc.fp = file->fp;
		file->fp = NULL; // lc now has ownership

		lc.name = file->path;
		lex_push(&lc);

		// print out each token
		fprintf(outfile, "# 1 \"%s\"\n", file->path);
		while (1)
		{
			lex();

			if (lex_token.type == LEX_TOKEN_TYPE_EOF) break;

			fprintf(outfile, "%s", lex_token.buf);
		}
	}

	fclose(outfile);
}
