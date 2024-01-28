#ifndef __LZD_CYCLIC_H__
#define __LZD_CYCLIC_H__
#include <stdlib.h>
#include <stddef.h>

static inline size_t // false index -> true index
CYC_INDEX (size_t index, size_t head, size_t size)
{
	return (index+head) % size;
}

static inline size_t // true index -> false index
CYC_UINDEX (size_t index, size_t head, size_t size)
{
	return abs((int)index-(int)head) % size;
}

static inline size_t
CYC_UROLL (size_t head, size_t amount, size_t size)
{
	return (head-amount) % size;
}

static inline size_t
CYC_ROLL (size_t head, size_t amount, size_t size)
{
	return (head+amount) % size;
}

#endif
