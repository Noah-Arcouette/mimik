#include <stdlib.h>
#include <unistd.h>

void 
exit (int status)
{
	while (__at_exit_amount)
	{
		__at_exit_funcs[--__at_exit_amount]();
	}

	_exit(status);
}
