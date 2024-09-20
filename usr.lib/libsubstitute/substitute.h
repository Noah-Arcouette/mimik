#ifndef __SUBSTITUTE_H__
#define __SUBSTITUTE_H__
#include <stddef.h>
#define __SUB_TYPE_VALUE 0
#define __SUB_TYPE_COMP  1
#define __SUB_TYPE_MASK  1

struct sub_out
{
    char  *data;
    size_t sz;
};

struct sub_map
{
    struct sub_map *parent;
    struct sub_map *child;
    struct sub_map *next;

    union {
        struct // child
        {
            int key;

            char flags;
            union {
                char *value;
                int(*comp)(struct sub_map *restrict, const char *restrict, size_t, struct sub_out *restrict);
            };
        };
        // root
        struct sub_out out;
    };
};

// init.c
struct sub_map *sub_init (void);

// <nulls>
void            sub_free (struct sub_map *);
struct sub_map *sub_copy (struct sub_map *);

int sub_del  (struct sub_map *restrict, const char *restrict key, size_t);
int sub_set  (struct sub_map *restrict, const char *restrict key, size_t, const char *restrict value, size_t);
int sub_comp (struct sub_map *restrict, const char *restrict key, size_t, int(*comp)(struct sub_map *restrict, const char *restrict, size_t, struct sub_out *restrict));

int sub_find (struct sub_map *restrict, struct sub_out *restrict, int c);

#endif
