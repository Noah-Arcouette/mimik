#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lzd.h"

int
main (void)
{
    struct LZD_Stream_Header header = {
        .magic = "LZD",
        .revision = 0,
        .dictionary = "",
        .diction = 8,
        .offset = 12,
        .length = 8,
        .history = 16
    };

    startWindow(header);

    pushWindow("hi", 2);
    pushWindow("hillo", 5);
    pushWindow("hallo", 5);
    pushWindow("ho", 2);
    findWindow("hillo", 5);
    struct LZD_Match match;
    matchWindow(&match);
    printf("%ld %ld\n", match.size, match.index);
    matchWindow(&match);
    printf("%ld %ld\n", match.size, match.index);
    matchWindow(&match);
    printf("%ld %ld\n", match.size, match.index);
    matchWindow(&match);
    printf("%ld %ld\n", match.size, match.index);

    stopWindow();

    return 0;
}

/*

 - Matching
 - Move-To-Front
 - Encoding

unsigned char *LZD_compress (struct LZD_Stream_Header, const unsigned char *buff, size_t size, size_t *outsize);

int start... (struct LZD_Stream_Header); // start the data structure
int stop...  ();                         // stop the data structure
int find...  (unsigned char *find);      // target sequence *find*
int match... (struct match *);           // find next match in the data structure
int push...  (unsigned char *buff, size_t size); // push data to the data structure

void encode (struct match, struct bits);

struct LZD_Match
{
    size_t        size;
    unsigned char type;
    union
    {
        size_t hst;
        size_t dct;
        struct
        {
            size_t off;
            size_t len;
        };
    };
};

*/
