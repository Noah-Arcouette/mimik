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
    case COMMENTS_STATE_POSSIBLE_COMMENT:
        switch (c)
        {
        case '/':
            state = COMMENTS_STATE_COMMENT;
            return;
        case '*':
            state = COMMENTS_STATE_MULTILINE_COMMENT;
            return;
        }
        fputc('/', fout);
        break;
    case COMMENTS_STATE_COMMENT:
        if (c != '\n')
        {
            return;
        }
        state = 0;
        break;
    case COMMENTS_STATE_MULTILINE_OUT:
        if (c == '/')
        {
            state = 0;
            return;
        }
        state = COMMENTS_STATE_MULTILINE_COMMENT;
    case COMMENTS_STATE_MULTILINE_COMMENT:
        if (c == '*')
        {
            state = COMMENTS_STATE_MULTILINE_OUT;
            return;
        }
        if (c != '\n')
        {
            return;
        }
        break;
    }
    // state 0 / default
    if (c == '/')
    {
        state = COMMENTS_STATE_POSSIBLE_COMMENT;
        return;
    }
out:
    fputc(c, fout);
}
