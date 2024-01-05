#ifndef __LZD_CYCLIC_H__
#define __LZD_CYCLIC_H__
#include <stddef.h>

static inline size_t
CYC_INDEX (size_t index, size_t head, size_t size)
{
    return (index+head) % size;
}

static inline size_t
CYC_UINDEX (size_t index, size_t head, size_t size)
{
    return (index-head) % size;
}

static inline size_t
CYC_ROLL (size_t head, size_t amount, size_t size)
{
    return (head-amount) % size;
}

#endif
