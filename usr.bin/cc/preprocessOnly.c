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

			switch (lex_token.type)
			{
			case LEX_TOKEN_TYPE_EOF:
				printf("eof\n");
				break;
			case LEX_TOKEN_TYPE_BITWISE_NOT:
				printf("~ ");
				break;
			case LEX_TOKEN_TYPE_LOGICAL_NOT:
				printf("! ");
				break;
			case LEX_TOKEN_TYPE_NOT_EQUALS:
				printf("!= ");
				break;
			case LEX_TOKEN_TYPE_HASH:
				printf("# ");
				break;
			case LEX_TOKEN_TYPE_MODULO:
				printf("%% ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_MODULO:
				printf("%%= ");
				break;
			case LEX_TOKEN_TYPE_XOR:
				printf("^ ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_XOR:
				printf("^= ");
				break;
			case LEX_TOKEN_TYPE_BITWISE_AND:
				printf("& ");
				break;
			case LEX_TOKEN_TYPE_LOGICAL_AND:
				printf("&& ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_AND:
				printf("&= ");
				break;
			case LEX_TOKEN_TYPE_MULTIPLY:
				printf("* ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_MULTIPLY:
				printf("*= ");
				break;
			case LEX_TOKEN_TYPE_OPEN_PAREN:
				printf("( ");
				break;
			case LEX_TOKEN_TYPE_CLOSE_PAREN:
				printf(") ");
				break;
			case LEX_TOKEN_TYPE_MINUS:
				printf("- ");
				break;
			case LEX_TOKEN_TYPE_DECREMENT:
				printf("-- ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_MINUS:
				printf("-= ");
				break;
			case LEX_TOKEN_TYPE_MEMBER:
				printf("-> ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN:
				printf("= ");
				break;
			case LEX_TOKEN_TYPE_EQUALS:
				printf("== ");
				break;
			case LEX_TOKEN_TYPE_PLUS:
				printf("+ ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_PLUS:
				printf("+= ");
				break;
			case LEX_TOKEN_TYPE_INCREMENT:
				printf("++ ");
				break;
			case LEX_TOKEN_TYPE_OPEN_CURLY:
				printf("{ ");
				break;
			case LEX_TOKEN_TYPE_CLOSE_CURLY:
				printf("} ");
				break;
			case LEX_TOKEN_TYPE_OPEN_SQUARE:
				printf("[ ");
				break;
			case LEX_TOKEN_TYPE_CLOSE_SQUARE:
				printf("] ");
				break;
			case LEX_TOKEN_TYPE_BITWISE_OR:
				printf("| ");
				break;
			case LEX_TOKEN_TYPE_LOGICAL_OR:
				printf("|| ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_OR:
				printf("|= ");
				break;
			case LEX_TOKEN_TYPE_SEMICOLON:
				printf("; ");
				break;
			case LEX_TOKEN_TYPE_COLON:
				printf(": ");
				break;
			case LEX_TOKEN_TYPE_STRING:
				printf("str<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_CHARACTER:
				printf("chr<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_GREATER:
				printf("> ");
				break;
			case LEX_TOKEN_TYPE_SHIFT_RIGHT:
				printf(">> ");
				break;
			case LEX_TOKEN_TYPE_ROLL_RIGHT:
				printf(">>> ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_ROLL_RIGHT:
				printf(">>>= ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_SHIFT_RIGHT:
				printf(">>= ");
				break;
			case LEX_TOKEN_TYPE_GREATER_OR_EQUAL:
				printf(">= ");
				break;
			case LEX_TOKEN_TYPE_LESSER:
				printf("< ");
				break;
			case LEX_TOKEN_TYPE_SHIFT_LEFT:
				printf("<< ");
				break;
			case LEX_TOKEN_TYPE_ROLL_LEFT:
				printf("<<< ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_ROLL_LEFT:
				printf("<<<= ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_SHIFT_LEFT:
				printf("<<= ");
				break;
			case LEX_TOKEN_TYPE_LESSER_OR_EQUAL:
				printf("<= ");
				break;
			case LEX_TOKEN_TYPE_COMMA:
				printf(", ");
				break;
			case LEX_TOKEN_TYPE_PERIOD:
				printf(". ");
				break;
			case LEX_TOKEN_TYPE_DIVIDE:
				printf("/ ");
				break;
			case LEX_TOKEN_TYPE_ASSIGN_DIVIDE:
				printf("/= ");
				break;
			case LEX_TOKEN_TYPE_TERTIARY:
				printf("? ");
				break;
			case LEX_TOKEN_TYPE_COMMENT:
				printf("cmt<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_WHITESPACE:
				printf("wht<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_NEWLINE:
				printf("\n ");
				break;
			case LEX_TOKEN_TYPE_SYMBOL:
				printf("sym<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_NUMBER:
				printf("num<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_DECIMAL:
				printf("dec<%s> ", lex_token.buf);
				break;
			case LEX_TOKEN_TYPE_ALIGNAS:
				printf("alignas ");
				break;
			case LEX_TOKEN_TYPE_ALIGNOF:
				printf("alignof ");
				break;
			case LEX_TOKEN_TYPE_AUTO:
				printf("auto ");
				break;
			case LEX_TOKEN_TYPE_BOOL:
				printf("bool ");
				break;
			case LEX_TOKEN_TYPE_BREAK:
				printf("break ");
				break;
			case LEX_TOKEN_TYPE_CASE:
				printf("case ");
				break;
			case LEX_TOKEN_TYPE_CHAR:
				printf("char ");
				break;
			case LEX_TOKEN_TYPE_CONST:
				printf("const ");
				break;
			case LEX_TOKEN_TYPE_CONSTEXPR:
				printf("constexpr ");
				break;
			case LEX_TOKEN_TYPE_CONTINUE:
				printf("continue ");
				break;
			case LEX_TOKEN_TYPE_DEFAULT:
				printf("default ");
				break;
			case LEX_TOKEN_TYPE_DO:
				printf("do ");
				break;
			case LEX_TOKEN_TYPE_DOUBLE:
				printf("double ");
				break;
			case LEX_TOKEN_TYPE_ELSE:
				printf("else ");
				break;
			case LEX_TOKEN_TYPE_ENUM:
				printf("enum ");
				break;
			case LEX_TOKEN_TYPE_EXTERN:
				printf("extern ");
				break;
			case LEX_TOKEN_TYPE_FLOAT:
				printf("float ");
				break;
			case LEX_TOKEN_TYPE_FOR:
				printf("for ");
				break;
			case LEX_TOKEN_TYPE_GOTO:
				printf("goto ");
				break;
			case LEX_TOKEN_TYPE_IF:
				printf("if ");
				break;
			case LEX_TOKEN_TYPE_INLINE:
				printf("inline ");
				break;
			case LEX_TOKEN_TYPE_INT:
				printf("int ");
				break;
			case LEX_TOKEN_TYPE_LONG:
				printf("long ");
				break;
			case LEX_TOKEN_TYPE_REGISTER:
				printf("register ");
				break;
			case LEX_TOKEN_TYPE_RESTRICT:
				printf("restrict ");
				break;
			case LEX_TOKEN_TYPE_RETURN:
				printf("return ");
				break;
			case LEX_TOKEN_TYPE_SHORT:
				printf("short ");
				break;
			case LEX_TOKEN_TYPE_SIGNED:
				printf("signed ");
				break;
			case LEX_TOKEN_TYPE_SIZEOF:
				printf("sizeof ");
				break;
			case LEX_TOKEN_TYPE_STATIC:
				printf("static ");
				break;
			case LEX_TOKEN_TYPE_STATIC_ASSERT:
				printf("static_assert ");
				break;
			case LEX_TOKEN_TYPE_STRUCT:
				printf("struct ");
				break;
			case LEX_TOKEN_TYPE_SWITCH:
				printf("switch ");
				break;
			case LEX_TOKEN_TYPE_THREAD_LOCAL:
				printf("thread_local ");
				break;
			case LEX_TOKEN_TYPE_TYPEDEF:
				printf("typedef ");
				break;
			case LEX_TOKEN_TYPE_TYPEOF:
				printf("typeof ");
				break;
			case LEX_TOKEN_TYPE_TYPEOF_UNQUAL:
				printf("typeof_unqual ");
				break;
			case LEX_TOKEN_TYPE_UNION:
				printf("union ");
				break;
			case LEX_TOKEN_TYPE_UNSIGNED:
				printf("unsigned ");
				break;
			case LEX_TOKEN_TYPE_VOID:
				printf("void ");
				break;
			case LEX_TOKEN_TYPE_VOLATILE:
				printf("volatile ");
				break;
			case LEX_TOKEN_TYPE_WHILE:
				printf("while ");
				break;
			case LEX_TOKEN_TYPE_ATOMIC:
				printf("_Atomic ");
				break;
			case LEX_TOKEN_TYPE_BITINT:
				printf("_BitInt ");
				break;
			case LEX_TOKEN_TYPE_COMPLEX:
				printf("_Complex ");
				break;
			case LEX_TOKEN_TYPE_COUNTOF:
				printf("_Countof ");
				break;
			case LEX_TOKEN_TYPE_DECIMAL32:
				printf("_Decimal32 ");
				break;
			case LEX_TOKEN_TYPE_DECIMAL64:
				printf("_Decimal64 ");
				break;
			case LEX_TOKEN_TYPE_DECIMAL128:
				printf("_Decimal128 ");
				break;
			case LEX_TOKEN_TYPE_GENERIC:
				printf("_Generic ");
				break;
			case LEX_TOKEN_TYPE_NORETURN:
				printf("_Noreturn ");
				break;
			case LEX_TOKEN_TYPE_PRAGMA:
				printf("_Pragma ");
				break;
			case LEX_TOKEN_TYPE_ASM:
				printf("__asm__ ");
				break;
			case LEX_TOKEN_TYPE_ATTRIBUTE:
				printf("__attribute__ ");
				break;
			case LEX_TOKEN_TYPE_NULLPTR:
				printf("nullptr ");
				break;
			case LEX_TOKEN_TYPE_TRUE:
				printf("true ");
				break;
			case LEX_TOKEN_TYPE_FALSE:
				printf("false ");
				break;
			case LEX_TOKEN_TYPE_ELLIPSES:
				printf("... ");
				break;
			case LEX_TOKEN_TYPE_UNKNOWN:
				printf("ukn<%s> ", lex_token.buf);
				break;
			}

			if (lex_token.type == LEX_TOKEN_TYPE_EOF) break;

			// fprintf(outfile, "%s", lex_token.buf);
		}
	}

	lex_free();
	fclose(outfile);
}
