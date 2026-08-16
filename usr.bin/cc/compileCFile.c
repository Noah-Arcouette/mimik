#include "parse.h"
#include "main.h"
#include "args.h"
#include "lex.h"

void
compileCFile (struct args_file *file)
{
	struct lex_context lc = {
		.type   = LEX_CONTEXT_TYPE_NORMAL_FILE,
		.lineno = 1,
		.offset = 0,
		.size   = 0,
		.name   = file->path,
		.fp     = file->fp
	};
	file->fp = NULL; // lc has ownership
	lex_push(&lc);

	// generate an AST
	struct ast ast;
	parse(&ast);

	// optimize the AST
	// assembler codegen

	parse_freeAST(&ast);
}
