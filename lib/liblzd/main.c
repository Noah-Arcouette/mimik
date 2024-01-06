#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lzd.h"

/*

struct entry
{
    unsigned char *buff;
    size_t         size;

    struct entry *next; // for the hash table
} entries[n]; // cyclic buffer

struct entry *hashtable[n]; the hash table

size_t        key   (buff, size);
struct entry *search(key);
void          add   (struct entry *);
void          remove(key);

*/

struct entry
{
    unsigned char *buff;
    size_t         size;

    struct entry *next;
};

#define SIZE 256

size_t ks;

size_t
key (unsigned char *buff, size_t size)
{
    size_t i = ks;

    while (size--)
    {
        srand(buff[size]);
        i ^= rand();
    }

    return 0;
    return i % SIZE;
}

void
add (struct entry **hashtable, struct entry *entry)
{
    size_t k = key(entry->buff, entry->size);
    
    struct entry **e = &hashtable[k];

    while (*e)
    {
        e = &(*e)->next;
    }

    *e = entry;
}

struct entry *
search (struct entry **hashtable, unsigned char *buff, size_t size)
{
    size_t k = key(buff, size);
    
    struct entry *e = hashtable[k];

    while (e)
    {
        if (e->size == size && !memcmp(e->buff, buff, size))
        {
            return e;
        }

        e = e->next;
    }
    return (struct entry *)NULL;
}

void
hremove (struct entry **hashtable, struct entry entry)
{
    size_t k = key(entry.buff, entry.size);
    
    struct entry *e     = hashtable[k];
    struct entry *prior = (struct entry *)NULL;

    while (e)
    {
        if (e->size == entry.size && !memcmp(e->buff, entry.buff, entry.size))
        {
            if (prior)
            {
                prior->next = e->next;
                return;
            }

            hashtable[k] = e->next;
        }

        prior = e;
        e     = e->next;
    }
}

int
main (void)
{
    srand(time(0));
    ks = rand();

    struct entry entries[SIZE];
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

    add(hashtable, &entries[0]);
    add(hashtable, &entries[1]);
    add(hashtable, &entries[2]);
    hremove(hashtable, entries[0]);
    hremove(hashtable, entries[1]);
    hremove(hashtable, entries[5]);

    printf("%s\n", search(hashtable, entries[2].buff, entries[2].size)->buff);

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
