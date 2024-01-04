#include "lzd.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned char *window;
static size_t         wsize;
static size_t         head;

int
startWindow (struct LZD_Stream_Header header)
{
    wsize  = pow(2, header.offset)+pow(2, header.length);
    head   = 0;
    window = malloc(wsize);

    if (!window)
    {
        return 1;
    }

#ifdef RESILIENT
    memchr(window, 0, wsize);
#endif
    return 0;
}

void 
stopWindow (void)
{
    free(window);
}

static unsigned char *search;
static size_t         widx; // index into the window
static size_t         sidx; // index into the search, the character to find

void
findWindow (unsigned char *find)
{
    search = find;
    widx   = 0;
    sidx   = 0;
}

// cyclic buffer to allow fast head appending
#define WINDOW_INDEX(i) (       (i + head) % wsize)
#define WINDOW_ROLL(s)  (head = (head - s) % wsize)

int
matchWindow (struct LZD_Match *match)
{
    for (; (widx+sidx)<wsize; widx++)
    {
        if (window[WINDOW_INDEX(widx+sidx)] == search[sidx])
        {
            // set match
            match->type  = LZD_MATCH_TYPE_WINDOW;
            match->size  = ++sidx; // stops an infinite loop from happening, find next character
            match->index = widx;
            return 0;
        }
        sidx = 0;
    }
    return 1;
}

int
pushWindow (unsigned char *buff, size_t size)
{
    WINDOW_ROLL(size);
    for (size_t i = 0; i<size; i++)
    {
        window[WINDOW_INDEX(i)] = buff[i];
    }

    return 0;
}
