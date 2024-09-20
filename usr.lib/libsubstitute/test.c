#include "substitute.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

int
main (void)
{
	struct sub_map *map = sub_init();

	if (!map)
	{
		printf("Error %d: %s", errno, strerror(errno));
	}

	sub_free(map);

    return 0;
}
