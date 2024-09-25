#include "substitute.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define __STR(x) #x
#define STR(x) __STR(x)
#define LINE STR(__LINE__)

int
testfunc (struct sub_map *restrict, const char *restrict, size_t, struct sub_out *restrict)
{
	return 0;
}

int
main (void)
{
	struct sub_map *map = sub_init();

	if (!map)
	{
		printf(LINE ": Error %d: %s", errno, strerror(errno));
		return 1;
	}

	if (sub_set(map, "Hello", 5, "Hello, world!", 14))
	{
		printf(LINE ": Error %d: %s", errno, strerror(errno));
		return 1;
	}

	if (sub_set(map, "Hi", 2, "Hello, world!", 14))
	{
		printf(LINE ": Error %d: %s", errno, strerror(errno));
		return 1;
	}

	sub_del(map, "Hi", 2);

	if (sub_comp(map, "Hey", 3, testfunc))
	{
		printf(LINE ": Error %d: %s", errno, strerror(errno));
		return 1;
	}

	if (!sub_set(map, "ERROR", 5, NULL, 0))
	{
		printf(LINE ": Not allowed.\n");
		return 1;
	}


	sub_del(map, "Hello",   5);
	sub_del(map, "Hey",     3);
	sub_del(map, "Nothing", 7);

	if (sub_comp(map, "Hie", 3, testfunc))
	{
		printf(LINE ": Error %d: %s", errno, strerror(errno));
		return 1;
	}

	sub_del(map, "Hie", 3);

	sub_rewind(map,  1);
	sub_rewind(map, -1);

	sub_free(map);

    return 0;
}
