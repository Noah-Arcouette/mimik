#include "substitute.h"
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>

static int
__sub_set (struct sub_map *restrict map, const char *restrict key, size_t keysz, const void *restrict value, size_t valsz, int type)
{
	struct sub_map *lastMatch = map;
	size_t keyi = 0; // current character in key

	// find closest match
	struct sub_map *currentMatch = map->child;
	while (currentMatch)
	{
		// full match, all characters in key matched
		if (keyi >= keysz)
		{
			goto set;
		}

		// child matches
		if (currentMatch->key == key[keyi])
		{
			keyi++; // next character
			lastMatch    = currentMatch;
			currentMatch = currentMatch->child; // go down one
			continue;
		}

		// next character
		currentMatch = currentMatch->next;
	}

	// keyi, last unmatched character in key
	// lastMatch, last non-null matched character in map

	// finish match, adding new character to map (adding to the linked list)
	struct sub_map *tail; // tail save
	while (keyi < keysz)
	{
		tail = lastMatch->child; // save tail
		// allocate
		lastMatch->child = (struct sub_map *)malloc(sizeof(struct sub_map));
		if (!lastMatch->child)
		{
			lastMatch->child = tail; // restore tail
			return 1; // leave with error
		}

		// initialize
		lastMatch->child->parent = lastMatch; // set parent
		lastMatch->child->next   = tail; // set tail
		// go down
		lastMatch = lastMatch->child;
		// continue initializing
		lastMatch->child = (struct sub_map *)NULL;
		lastMatch->key   = key[keyi];
		lastMatch->flags = __SUB_TYPE_NONE;

		keyi++; // next character in key
	}
	// set data
set:
	// free previous value, if any
	if ((lastMatch->flags & __SUB_TYPE_MASK) == __SUB_TYPE_VALUE)
	{
		free(lastMatch->value);
	}

	// add value key
	if (type == __SUB_TYPE_VALUE)
	{
		// allocate
		lastMatch->value = (char *)malloc(valsz);
		if (!lastMatch->value) // failed
		{
			int error = errno;

			// remove afflicted node
			lastMatch->flags = __SUB_TYPE_NONE; // don't free data
			// sub_del(map, key, keysz); // delete node

			errno = error; // restore errno
			return 1; // error
		}

		lastMatch->flags = (lastMatch->flags & ~__SUB_TYPE_VALUE) | __SUB_TYPE_NONE; // set value type, and preserve other flags
		memcpy(lastMatch->value, value, valsz); // copy data
		return 0; // success
	}
	// compute value
	lastMatch->flags = (lastMatch->flags & ~__SUB_TYPE_VALUE) | __SUB_TYPE_COMP; // set value type, and preserve other flags
	lastMatch->comp = (int(*)(struct sub_map *restrict, const char *restrict, size_t, struct sub_out *restrict))value; // please take a moment to look at that beautiful, redundant, cast
	return 0;
}

int
sub_set (struct sub_map *restrict map, const char *restrict key, size_t keysz, const char *restrict value, size_t valsz)
{
	if (!map || !key || !keysz || !value || !valsz)
	{
		errno = EINVAL;
		return 1;
	}

	return __sub_set(map, key, keysz, value, valsz, __SUB_TYPE_VALUE);
}

int
sub_comp (struct sub_map *restrict map, const char *restrict key, size_t keysz, int(*comp)(struct sub_map *restrict, const char *restrict key, size_t, struct sub_out *restrict))
{
	if (!map || !key || !keysz || !comp)
	{
		errno = EINVAL;
		return 1;
	}

	return __sub_set(map, key, keysz, comp, 0, __SUB_TYPE_COMP);
}
