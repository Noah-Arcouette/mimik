#ifndef __LZ_DUAL_HASH_TABLE_H__
#define __LZ_DUAL_HASH_TABLE_H__
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct entry
{
    unsigned char *buff;
    size_t         size;

    struct entry *next;
};

static size_t ks;

static size_t
hkey (unsigned char *buff, size_t size, size_t mod)
{
    size_t i = ks;

    while (size--)
    {
        srand(buff[size]);
        i ^= rand();
    }

    return i % mod;
}

static void
hadd (struct entry **hashtable, struct entry *entry, size_t mod)
{
    size_t k = hkey(entry->buff, entry->size, mod);
    
    struct entry **e = &hashtable[k];

    while (*e)
    {
        e = &(*e)->next;
    }

    *e = entry;
}

static struct entry *
hsearch (struct entry **hashtable, unsigned char *buff, size_t size, size_t mod)
{
    size_t k = hkey(buff, size, mod);
    
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

static void
hremove (struct entry **hashtable, struct entry entry, size_t mod)
{
    size_t k = hkey(entry.buff, entry.size, mod);
    
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

#endif
