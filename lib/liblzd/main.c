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

    if (startHistory(header))
    {
        printf("Failed to initialize history.\n");
        return 1;
    }

    if (pushHistory("Hello, world!", 14))
    {
        printf("Failed to push to history.\n");
        return 1;
    }
    if (pushHistory("Hi, world!", 11))
    {
        printf("Failed to push to history.\n");
        return 1;
    }
    if (pushHistory("Hell", 4))
    {
        printf("Failed to push to history.\n");
        return 1;
    }
    if (pushHistory("Hello", 5))
    {
        printf("Failed to push to history.\n");
        return 1;
    }

    findHistory("Hello, world!", 14);

    struct LZD_Match match;
    int              end;
    do
    {
        end = matchHistory(&match);

        if (match.size)
        {
            printf("[%ld] %ld\n", match.index, match.size);
        }
    } while (end);

    stopHistory();

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
