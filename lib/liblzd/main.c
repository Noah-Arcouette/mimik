#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hashtab.h"
#include "lzd.h"

#define SIZE 0xff+1

int
main (void)
{
    srand(time(0));
    ks = rand();

    struct entry *entries    = malloc(sizeof(struct entry) * SIZE);
    struct entry **hashtable = malloc(sizeof(struct entry *)*SIZE);

    for (int i = 0; i<SIZE; i++)
    {
        entries[i].buff = (unsigned char*)NULL;
        entries[i].size = 0;
        entries[i].next = (struct entry*)NULL;
        hashtable[i]    = (struct entry*)NULL;
    }

    entries[0].buff = (unsigned char*)"hi";
    entries[0].size = 3;
    entries[1].buff = (unsigned char*)"hello";
    entries[1].size = 6;
    entries[2].buff = (unsigned char*)"potato";
    entries[2].size = 6;

    hadd(hashtable, &entries[0], SIZE);
    hadd(hashtable, &entries[1], SIZE);
    hadd(hashtable, &entries[2], SIZE);
    hremove(hashtable, entries[0], SIZE);
    hremove(hashtable, entries[1], SIZE);
    hremove(hashtable, entries[5], SIZE);

    printf("%s\n", hsearch(hashtable, entries[2].buff, entries[2].size, SIZE)->buff);

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
