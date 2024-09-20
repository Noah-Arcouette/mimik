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

struct sub_map *sub_init (void);

#endif
