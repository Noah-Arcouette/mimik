#include "pipeline.h"
#include "globs.h"
#include <stdio.h>
#define COMMENTS_STATE_POSSIBLE_COMMENT  1
#define COMMENTS_STATE_COMMENT           2
#define COMMENTS_STATE_MULTILINE_COMMENT 3
#define COMMENTS_STATE_MULTILINE_OUT     4

void
comments (int c)
{
    static int state = 0;

    switch (state)
    {
	// possibly in a comment, the first `/`
    case COMMENTS_STATE_POSSIBLE_COMMENT:
        switch (c)
        {
        case '/': // single line
            state = COMMENTS_STATE_COMMENT;
            return;
        case '*': // multiline
            state = COMMENTS_STATE_MULTILINE_COMMENT;
            return;
        }
		// failed possibly match
        fputc('/', fout); // emit hold `/`
        break; // continue to nothing
    case COMMENTS_STATE_COMMENT: // in single line comment
        if (c != '\n') // print all but newlines
        {
            return;
        }
        state = 0; // on newline reset and print it
        break;
    case COMMENTS_STATE_MULTILINE_OUT: // possibly leaving a multiline, first `*`
        if (c == '/') // next is `/` successfully left the multiline
        {
            state = 0; // reset
            return; // no print
        }
        state = COMMENTS_STATE_MULTILINE_COMMENT; // reset into the full multiline comment
		// continue as if this didn't happen
    case COMMENTS_STATE_MULTILINE_COMMENT: // in multiline comment
        if (c == '*') // possibly leaving
        {
            state = COMMENTS_STATE_MULTILINE_OUT;
            return; // don't emit
        }
        if (c != '\n') // only emit newline
        {
            return;
        }
        break;
    }
    // state 0 / default
    if (c == '/') // possibly in comment
    {
        state = COMMENTS_STATE_POSSIBLE_COMMENT;
        return; // don't emit
    }
    fputc(c, fout); // output character as normal
}
