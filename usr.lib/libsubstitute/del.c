#include "substitute.h"
#include <stdlib.h>
#include <stdio.h>

void
sub_del (struct sub_map *restrict map, const char *restrict key, size_t keysz)
{
	// check for nulls
	if (!map || !key || !keysz)
	{
		return;
	}

	struct sub_map *current = map->child;
	// find key
	struct sub_map *hold; // last valid character
	while (keysz) // check whole of the key
	{
		// cannot find match
		if (!current)
		{
			return; // leave
		}

		// successful match
		if (current->key == *key)
		{
			hold    = current; // save last matched character
			current = current->child; // go down one

			// next key
			key++;
			keysz--;

			continue;
		}

		// next
		current = current->next;
	}

	// clear value
	if ((hold->flags & __SUB_TYPE_MASK) == __SUB_TYPE_VALUE)
	{
		free(hold->value);
		hold->valuesz = 0;
	}
	hold->flags = __SUB_TYPE_NONE; // clear data flags

	// free as much as possible (garbage collections)
	current = hold;
	while (
		current && // make sure current exists
		current != map && // don't free the very top map
		!current->child && // no children
		((current->flags & __SUB_TYPE_MASK) == __SUB_TYPE_NONE) // no data
	)
	{
		// save the parent
		hold = current->parent;

		// // remove from linked list
		if (current->previous) // not root
		{
			current->previous->next = current->next;
			if (current->next) // end of list
			{
				current->next->previous = current->previous;
			}
		}
		else if (current->parent) // root
		{
			current->parent->child = current->next;
			if (current->next) // end of list
			{
				current->next->previous = (struct sub_map *)NULL;
			}
		}

		// free
		free(current);

		// next
		current = hold;
	}
}
