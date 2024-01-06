#include "lzd.h"
#include "cyclic.h"
#include "hashtab.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static struct entry  *entries;
static struct entry **hashtable;
static size_t         esize;

static size_t head;

int
startHistory (struct LZD_Stream_Header header)
{
    srand(time(0));
    ks    = rand();
    esize = pow(2, header.history)+1;
    head  = 0;

    entries   = malloc(sizeof(struct entry) * esize);
    hashtable = malloc(sizeof(struct entry *)*esize);

    if (!entries || !hashtable)
    {
        return 1;
    }

    for (size_t i = 0; i<esize; i++)
    {
        entries[i].buff = (unsigned char*)NULL;
        entries[i].size = 0;
        entries[i].next = (struct entry*)NULL;
        hashtable[i]    = (struct entry*)NULL;
    }

    return 0;
}

void 
stopHistory (void)
{
    for (size_t i = 0; i<esize; i++)
    {
        free(entries[i].buff);
    }

    free(entries);
    free(hashtable);
}

static unsigned char *search;
static size_t         ssize;
static size_t         checksize;

void
findHistory (unsigned char *find, size_t findSize)
{
    search    = find;
    ssize     = findSize;
    checksize = 2;
}


int
matchHistory (struct LZD_Match *match)
{
    struct entry *found = hsearch(hashtable, search, checksize, esize);

    if (!found)
    {
        match->size = 0;
    }
    else
    {
        match->size  = checksize;
        match->type  = LZD_MATCH_TYPE_HISTORY;
        match->index = CYC_UINDEX(found-entries,head,esize);
    }

    return ssize-checksize++;
}

int
pushHistory (unsigned char *buff, size_t size)
{
    // roll back
    head     = CYC_ROLL(head,1,esize);
    size_t i = CYC_INDEX(0,head,esize);
    
    // remove old
    free(entries[i].buff);
    hremove(hashtable, entries[i], esize);

    // allocate new
    entries[i].buff = malloc(size * sizeof(unsigned char));
    if (!entries[i].buff)
    {
        return 1;
    }

    memcpy(entries[i].buff, buff, size);
    entries[i].size = size;
    entries[i].next = (struct entry *)NULL;

    // add new
    hadd(hashtable, &entries[i], esize);

    return 0;
}
