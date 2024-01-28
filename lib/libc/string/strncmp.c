#include <string.h>
#include <stddef.h>

int
strncmp (const char *s1, const char *s2, size_t n)
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

	while (*s1 == *s2 && n)
	{
		if (!*s1)
		{
			return 0;
		}

		s1++;
		s2++;
		n--;
	}

	if (n)
		return *s1 - *s2;
	return 0;
}
