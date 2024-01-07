#include <lzd.h>
#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
    struct LZD_Stream_Header header = 
    {
        .magic = "LZD",
        .revision = 0,
        .dictionary = "",
        .diction = 8,
        .offset = 12,
        .length = 8,
        .history = 16
    };

    if (startDictionary(header))
    {
        puts("liblzd/diction 21: Failed to start dictionary of size 8");
        return 1;
    }

    int err = 0;

    // test first character
    findDictionary((unsigned char *)"\0\0\0", 4);
    struct LZD_Match match;
    if (!matchDictionary(&match))
    {
        puts("liblzd/diction 32: Matches multiple zeros");
        err = 1;
    }
    if (match.size != 1)
    {
        puts("liblzd/diction 37: Cannot match zero, or match many zeros");
        err = 1;
    }
    if (match.index)
    {
        puts("liblzd/diction 42: Mismatches zero");
        err = 1;
    }

    // test last character
    findDictionary((unsigned char *)"\xff\xff\xff\xff", 4);
    if (!matchDictionary(&match))
    {
        puts("liblzd/diction 51: Matches multiple 255s");
        err = 1;
    }
    if (match.size != 1)
    {
        puts("liblzd/diction 56: Cannot match 255, or match many 255s");
        err = 1;
    }
    if (match.index != 0xff)
    {
        puts("liblzd/diction 61: Mismatches 255");
        err = 1;
    }

    // test random character
    findDictionary((unsigned char *)"\x77\x77\x77\x77", 4);
    if (!matchDictionary(&match))
    {
        puts("liblzd/diction 68: Matches multiple 77s");
        err = 1;
    }
    if (match.size != 1)
    {
        puts("liblzd/diction 73: Cannot match 77, or match many 77s");
        err = 1;
    }
    if (match.index != 0x77)
    {
        puts("liblzd/diction 78: Mismatches 77");
        err = 1;
    }

    stopDictionary();

    if (err)
    {
        puts("liblzd/diction:\tInconsistent!");
        return err;
    }

    puts("liblzd/diction:\tConsistent");
    return 0;
}
