#include <nl_types.h>
#include <stdio.h>

#ifndef NLS
char *
catgets (nl_catd, int, int, const char *msg)
{
	return (char *)msg;
}
#else

#endif
