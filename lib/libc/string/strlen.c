#include <string.h>

size_t
strlen (const char *s)
{
#ifdef RESILIENT
	if (!s)
	{
		return 0;
	}
#endif

	size_t sz = 0;

	while (*s)
	{
		s++;
		sz++;
	}

	return sz;
}

size_t
strnlen (const char *s, size_t n)
{
#ifdef RESILIENT
	if (!s)
	{
		return 0;
	}
#endif

	size_t sz = 0;

	while (*s && n)
	{
		s++;
		sz++;
		n--;
	}

	return sz;
}

