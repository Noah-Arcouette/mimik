#include <string.h>
#include <stddef.h>

int
memcmp (const void *s1, const void *s2, size_t n)
{
#ifdef RESILIENT
	if (!s1 && !s2)
	{
		return 0;
	}
	if (!s1)
	{
		return -1;
	}
	if (!s2)
	{
		return 1;
	}
#endif

	register char r;
	while (n--)
	{
		r = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (r)
			return r;
	}

	return 0;
}
