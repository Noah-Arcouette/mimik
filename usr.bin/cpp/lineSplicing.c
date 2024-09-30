#include <stdio.h>
#include "pipeline.h"
#include "globs.h"

void
lineSplicing (int c)
{
    static int hold     = 0; // hold output and check next character
    static int captured = 0; // amount of newlines captured

    // check if we should hold output
    if (c == '\\')
    {
        hold = 1;
        return;
    }
    // holding output
    if (hold)
    {
        // only hold two character
        hold = 0;

        // true hold
        if (c == '\n')
        {
            captured++; // capture newline and remove held `\'
            return;
        }

        // false hold, output data
        comments('\\');
    }
    else if (c == '\n') // on non-captured newline
    {
        // output backed up newlines
        while (captured)
        {
            comments('\n');
            captured--;
        }
    }

    // output character
    comments(c);
}
