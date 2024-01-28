#include <lzd.h>
#include <stdio.h>
#include <stdlib.h>

#define TITLE(x) printf("liblzd/%s %d: ", __FILE__, __LINE__)

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
        TITLE();
        puts("Failed to start dictionary of size 8");
        return 1;
    }

    int err = 0;

    // test first character
    findDictionary((unsigned char *)"\0\0\0", 4);
    struct LZD_Match match;
    if (!matchDictionary(&match))
    {
        TITLE();
        puts("Matches multiple zeros");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Cannot match zero, or match many zeros");
        err = 1;
    }
    if (match.index)
    {
        TITLE();
        puts("Mismatches zero");
        err = 1;
    }

    // test last character
    findDictionary((unsigned char *)"\xff\xff\xff\xff", 4);
    if (!matchDictionary(&match))
    {
        TITLE();
        puts("Matches multiple 255s");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Cannot match 255, or match many 255s");
        err = 1;
    }
    if (match.index != 0xff)
    {
        TITLE();
        puts("Mismatches 255");
        err = 1;
    }

    // test random character
    findDictionary((unsigned char *)"\x77\x77\x77\x77", 4);
    if (!matchDictionary(&match))
    {
        TITLE();
        puts("Matches multiple 77s");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Cannot match 77, or match many 77s");
        err = 1;
    }
    if (match.index != 0x77)
    {
        TITLE();
        puts("Mismatches 77");
        err = 1;
    }

    stopDictionary();

    if (err)
    {
        TITLE();
        puts("\tInconsistent!");
        return err;
    }

    TITLE();
    puts("\tConsistent");
    return 0;
}
