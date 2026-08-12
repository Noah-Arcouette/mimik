#include "../lex.h"
#include <libintl.h>
#include <stdarg.h>
#include <stdio.h>

static void
_printContext (long index)
{
	if (index < 0) return;

	// print the prior context
	_printContext(index-1);

	struct lex_context *lc = &lex_context[index];
	switch (lc->type)
	{
	case LEX_CONTEXT_TYPE_NORMAL_FILE:
		fprintf(stderr, gettext("\nIn file `%s' line %d: "),
			lc->name, lc->lineno);
		break;
	}
}

void
lex_prettyprint (const char *fmt, ...)
{
	if (!lex_contexts) goto _msg;

	// print the context stack
	_printContext(lex_contexts-1);
	struct lex_context *lc = &lex_context[lex_contexts-1];

	// find the line
	off_t coff = ftello(lc->fp);
	if (coff < 0) goto _msg;
	if (fseeko(lc->fp, 0, SEEK_SET) < 0) goto _msg;

	int lineno = 1;
	int gotLine = 0;
	while (1)
	{
		if (lineno == lc->lineno)
		{
			gotLine = 1;
			break;
		}

		int c = fgetc(lc->fp);
		if (c == EOF) break;
		if (c == '\n') lineno++;
	}

	// print the line
	if (gotLine)
	{
		int offset = 0;
		while (1)
		{
			int c = fgetc(lc->fp);
			if (c == EOF) break;
			if (c == '\n') break;

			if (offset == lc->offset)
			{
				fprintf(stderr, "\x1b[4m");
			}
			else if (offset == (lc->offset+lc->size))
			{
				fprintf(stderr, "\x1b[0m");
			}

			fputc(c, stderr);

			offset++;
		}
		fprintf(stderr, "\x1b[0m");
	}

	fseeko(lc->fp, coff, SEEK_SET);
_msg:
// print the message
	fprintf(stderr, "\n\t");
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}
