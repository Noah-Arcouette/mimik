#include "lzd.h"
#include <string.h>

int presetDiction;

int
startDictionary (struct LZD_Stream_Header header)
{
    presetDiction = 0;
    if (!strcmp(header.dictionary, ""))
    {
        presetDiction = 1;
        return 0;
    }

    return 1;
}

void
stopDictionary (void)
{
    return;
}

unsigned char *search;

void
findDictionary (unsigned char *find)
{
    search = find;
}

int
matchDictionary (struct LZD_Match *match)
{
    match->type = LZD_MATCH_TYPE_DICTION;
    if (presetDiction)
    {
        match->size = 1;
        match->dct  = search[0];
    }

    return 1;
}
