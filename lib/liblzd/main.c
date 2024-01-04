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
    if (startWindow(header))
    {
        printf("Cannot create window\n");
        return 1;
    }
    struct LZD_Match match;

    pushWindow((unsigned char *)"Hello, world!", 13);
    pushWindow((unsigned char *)"W", 1);
    pushWindow((unsigned char *)"Hello, world!", 13);
    pushWindow((unsigned char *)"W", 1);
    pushWindow((unsigned char *)"Hello, world!", 13);
    pushWindow((unsigned char *)"W", 1);

    findWindow((unsigned char *)"Hello");

    while (!matchWindow(&match))
    {
        printf("%ld %ld\n", match.size, match.index);
    }

    stopWindow();

    return 0;
}

/*

 - History
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
