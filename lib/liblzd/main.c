#include <stdio.h>
#include <string.h>
#include "lzd.h"

int
main (void)
{
    struct LZD_Stream_Header header = {
        .magic      = "LZD",
        .revision   = 0,
        .dictionary = "",
        .diction    = 8,
        .offset     = 16,
        .length     = 8,
        .history    = 12
    };
    if (startDictionary(header))
    {
        printf("Cannot open dictionary\n");
        return 1;
    }
    struct LZD_Match match;

    findDictionary((unsigned char *)"Hello, world!");
    matchDictionary(&match);

    printf("%ld %02lx\n", match.size, match.dct);

    stopDictionary();

    return 0;
}

/*

 - Dictionary
 - Window
 - History
 - Matching
 - Move-To-Front
 - Encoding

unsigned char *LZD_compress (struct LZD_Stream_Header, const unsigned char *buff, size_t size, size_t *outsize);

int start... (struct LZD_Stream_Header); // start the data structure
int stop...  ();                         // stop the data structure
int find...  (unsigned char *find);      // target sequence *find*
int match... (struct match *);           // find next match in the data structure

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
