#ifndef __LZ_DUAL_MOVE_TO_FRONT_H__
#define __LZ_DUAL_MOVE_TO_FRONT_H__
#include <stdlib.h>
#include <stdio.h>

static unsigned char* list;

static int
startMtf ()
{
	list = (unsigned char*)malloc(256*sizeof(unsigned char));
	if (!list)
	{
		return 1;
	}

	for (int i = 0; i<256; i++)
	{
		list[i] = i;
	}

	return 0;
}

static int
encodeMtf (int in)
{
	// transform
	int buff;
	for (int i = 0; i<256; i++)
	{
		if (list[i] == in)
		{
			for (int j = i-1; j+1; j--)
			{
				buff      = list[j];
				list[j]   = list[j+1];
				list[j+1] = buff;
			}

			return i;
		}
	}

	return -1;
}

static void
stopMtf ()
{
	free(list);
}

#endif
