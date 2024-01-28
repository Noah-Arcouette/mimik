#include <string.h>
#include <nl_types.h>

char *
strerror (int error)
{
	return catgets(__errno_catd, 1, error, "Unknown error");
}
