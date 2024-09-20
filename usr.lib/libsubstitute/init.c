#include "substitute.h"
#include <stddef.h>
#include <stdlib.h>

struct sub_map *
sub_init (void)
{
	// allocate
	struct sub_map *map = (struct sub_map *)malloc(sizeof(struct sub_map));
	if (!map)
	{
		return (struct sub_map *)NULL;
	}

	// initialize
	map->parent = (struct sub_map *)NULL; // root
	map->child  = (struct sub_map *)NULL;
	map->next   = (struct sub_map *)NULL;

	map->out.data = (char *)NULL;
	map->out.sz   = 0;

    return map;
}
