#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "main.h"

const char *self;

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("as");

	self = argv[0];

	// parse arguments
	if (args(argc, argv))
	{
		return 1;
	}

	// lexer testing
	int errors = 0;
	struct token tok;
	createToken(&tok);
	for (int i = optind; i<argc; i++)
	{
		// open the file
		FILE *fp;
		if (!strcmp(argv[i], "-"))
		{
			fp = stdin;
		}
		else
		{
			fp = fopen(argv[i], "r");
			if (!fp)
			{
				int error = errno;
				fprintf(stderr, gettext("%s: %s, %s\n"),
					argv[0], argv[i], strerror(error));
				errors = 1;
				continue;
			}
		}

		do
		{
			// get each token
			if (lex(argv[i], fp, &tok)) break;

			// print it
			switch (tok.type)
			{
			case TOK_ARCH:
				printf(".arch ");
				break;
			case TOK_COLON:
				printf(": ");
				break;
			case TOK_EOF:
				printf("eof\n");
				break;
			case TOK_GLOBAL:
				printf(".global ");
				break;
			case TOK_NEWLINE:
				printf("\n");
				break;
			case TOK_UNKNOWN:
				printf("ukn<%s> ", tok.buf);
				break;
			case TOK_SECTION:
				printf(".section ");
				break;
			case TOK_SYMBOL:
				printf("sym<%s> ", tok.buf);
				break;
			}
		} while (tok.type != TOK_EOF);

		// close the file
		fclose(fp);

		resetToken(&tok);
	}
	destroyToken(&tok);


	// parser:
	//  - sections
	//  - architecture
	//  - symbols
	//  - gaps
	//  - emit data
	//  - reserve data
	//  - x86-16
	// create architecture section
	// create symbol section
	// create gap section
	// emit the mio file

	return errors;
}
