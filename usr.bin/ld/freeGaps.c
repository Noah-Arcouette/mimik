#include "main.h"
#include <stdlib.h>

void
freeGaps (void)
{
	outputGapsz = 0;
	outputGapcp = 0;
	free(outputGap);
	outputGap = NULL;
}
