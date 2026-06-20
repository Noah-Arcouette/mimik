#include "main.h"
#include <stdlib.h>

void
closeInputFiles (void)
{
	while (inputs--)
	{
		free(input[inputs].data);
	}
	free(input);
	input = NULL;
}
