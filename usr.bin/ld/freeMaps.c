#include "main.h"
#include <stdlib.h>

void
freeMaps (void)
{
	free(outputMap);
	outputMap  = NULL;
	outputMaps = 0;
}
