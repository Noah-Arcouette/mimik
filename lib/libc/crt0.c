#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void);

void
_start (void)
{
	__init_stdio();
	__init_string();

	exit(main());

	__fini_string();
}
