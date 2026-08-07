#include "main.h"
#include "args.h"
#include "ast.h"
#include "lex.h"
#include <stdio.h>

void
compileCFiles (void)
{
	for (long i = 0; i<args_files; i++)
	{
		struct args_file *file = &args_file[i];

		// only manage C files
		if (file->type != ARGS_FILE_TYPE_C) continue;

		struct ast *ast = ast_generate(file->path, file->fp);
		fclose(file->fp);
		file->fp = NULL;

		// ast_rundown(file->path, ast);
		// ast_generateIR(file, ast);
		// ast_free(ast);
	}
	lex_free();
}
