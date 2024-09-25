#include "substitute.h"

void
sub_rewind (struct sub_map *map, int n)
{
	if (n < 0)
	{
		map->current = (struct sub_map *)NULL;
		return;
	}

	while (map->current && map->current->parent && n--)
	{
		map->current = map->current->parent;
	}
}
