#ifndef __SUBSTITUTE_H__
#define __SUBSTITUTE_H__
#include <stddef.h>
#define __SUB_TYPE_NONE  0b00
#define __SUB_TYPE_VALUE 0b01
#define __SUB_TYPE_COMP  0b10
#define __SUB_TYPE_MASK  0b11

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
	struct sub_map *previous;

    union {
        struct // child
        {
            int key;

            char flags;
            union {
				struct
				{
                	char  *value;
					size_t valuesz;
				};
                int(*comp)(struct sub_map *restrict, const char *restrict, size_t, struct sub_out *restrict);
            };
        };
        struct // root
		{
			struct sub_map *current;
        	struct sub_out  out;
		};
    };
};

// init.c
extern struct sub_map *sub_init (void);

// free.c
extern void sub_free (struct sub_map *);

// set.c
extern int sub_set  (struct sub_map *restrict, const char *restrict key, size_t, const char *restrict value, size_t);
extern int sub_comp (struct sub_map *restrict, const char *restrict key, size_t, int(*comp)(struct sub_map *restrict, const char *restrict key, size_t, struct sub_out *restrict));

// del.c
extern void sub_del (struct sub_map *restrict, const char *restrict key, size_t);

// <nulls>
extern struct sub_map *sub_copy (struct sub_map *);

extern int sub_find   (struct sub_map *restrict, struct sub_out *restrict, int c); // -1/EOF to emit last match

#endif
