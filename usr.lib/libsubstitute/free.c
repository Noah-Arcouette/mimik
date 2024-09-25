#include "substitute.h"
#include <stdlib.h>

void
sub_free (struct sub_map *map)
{
	// if root
	if (!map->parent)
	{
		// free data
		if (map->out.data)
		{
			free(map->out.data);
		}
		if (map->out.pushback)
		{
			free(map->out.pushback);
		}
	}

	// free sibling
	if (map->next)
	{
		sub_free(map->next);
	}

	// free child
	if (map->child)
	{
		sub_free(map->child);
	}

	// free value
	if ((map->flags & __SUB_TYPE_MASK) == __SUB_TYPE_VALUE)
	{
		free(map->value);
	}

	// free self
	free(map);
}
